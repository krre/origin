#include "RaycastOctreeRenderer.h"
#include "Graphics/Render/RenderManager.h"
#include "Base/Window.h"
#include "Vulkan/API/Framebuffer.h"
#include "Vulkan/API/Command/CommandBuffer.h"
#include "Vulkan/API/RenderPass.h"
#include "Vulkan/API/Descriptor/DescriptorSets.h"
#include "Vulkan/API/Pipeline/PipelineLayout.h"
#include "Graphics/Render/RenderManager.h"
#include "Vulkan/ShaderProgram.h"
#include "Vulkan/GpuBuffer.h"
#include "Vulkan/API/Pipeline/GraphicsPipeline.h"
#include "Resource/ResourceManager.h"
#include <glm/gtc/matrix_transform.hpp>

RaycastOctreeRenderer::RaycastOctreeRenderer(Object* parent) : OctreeRenderer(parent) {
    std::vector<glm::vec2> plane = {
       { -1.0, 1.0 }, { -1.0, -1.0 }, { 1.0, -1.0 },
        { -1.0, 1.0 }, { 1.0, -1.0 }, { 1.0, 1.0 }
    };

    Vulkan::Device* device = getDevice();

    vertextCount = plane.size();

    int size = plane.size() * sizeof(glm::vec2);
    vertexBuffer = std::make_unique<Vulkan::GpuBuffer>(device, VK_BUFFER_USAGE_VERTEX_BUFFER_BIT, size);
    vertexBuffer->write(plane.data(), size);

    shaderProgram = std::make_unique<Vulkan::ShaderProgram>(device);
    shaderProgram->loadShader(ResourceManager::get()->getDataPath() + "/Shader/RaycastOctree.vert.spv");
    shaderProgram->loadShader(ResourceManager::get()->getDataPath() + "/Shader/RaycastOctree.frag.spv");

    uboBuffer = std::make_unique<Vulkan::GpuBuffer>(device, VK_BUFFER_USAGE_UNIFORM_BUFFER_BIT, sizeof(UBO));

    VkDescriptorBufferInfo bufferInfo = {};
    bufferInfo.buffer = uboBuffer->getHandle();
    bufferInfo.range = VK_WHOLE_SIZE;
    shaderProgram->bindBuffer("ubo", bufferInfo);

    blocksBuffer = std::make_unique<Vulkan::GpuBuffer>(device, VK_BUFFER_USAGE_STORAGE_BUFFER_BIT, 1000000); // TODO: Use size from constant

    bufferInfo.buffer = blocksBuffer->getHandle();
    bufferInfo.range = VK_WHOLE_SIZE;
    shaderProgram->bindBuffer("blocks", bufferInfo);

    metaBuffer = std::make_unique<Vulkan::GpuBuffer>(device, VK_BUFFER_USAGE_STORAGE_BUFFER_BIT, 100000); // TODO: Use size from constant

    bufferInfo.buffer = metaBuffer->getHandle();
    bufferInfo.range = VK_WHOLE_SIZE;
    shaderProgram->bindBuffer("meta", bufferInfo);

    shaderProgram->create();

    graphicsPipeline = std::make_unique<Vulkan::GraphicsPipeline>(device);
    graphicsPipeline->setRenderPass(RenderManager::get()->getRenderPass()->getHandle());
    graphicsPipeline->setPipelineLayout(shaderProgram->getPipelineLayout()->getHandle());

    graphicsPipeline->addDynamicState(VK_DYNAMIC_STATE_VIEWPORT);
    graphicsPipeline->addDynamicState(VK_DYNAMIC_STATE_SCISSOR);

    for (auto& shader : shaderProgram->getShaders()) {
        graphicsPipeline->addShaderCode(shader->getStage(), shader->getCode().size() * sizeof(uint32_t), shader->getCode().data(), "main");
    }

    VkVertexInputBindingDescription bindingDescription;
    bindingDescription.binding = 0;
    bindingDescription.stride = sizeof(glm::vec2);
    bindingDescription.inputRate = VK_VERTEX_INPUT_RATE_VERTEX;
    graphicsPipeline->addVertexBindingDescription(bindingDescription);

    {
        const Vulkan::Shader::LocationInfo locationInfo = shaderProgram->getLocationInfo("position");
        VkVertexInputAttributeDescription attributeDescription = {};
        attributeDescription.binding = bindingDescription.binding;
        attributeDescription.location = locationInfo.location;
        attributeDescription.format = locationInfo.format;
        graphicsPipeline->addVertexAttributeDescription(attributeDescription);
    }

    graphicsPipeline->create();

    blocks.push_back(0xFF0000FF);
}

RaycastOctreeRenderer::~RaycastOctreeRenderer() {

}

void RaycastOctreeRenderer::writeCommandBuffer(Vulkan::CommandBuffer* commandBuffer, Vulkan::Framebuffer* framebuffer [[maybe_unused]]) {
    commandBuffer->bindPipeline(graphicsPipeline.get());

    commandBuffer->clearVertexBuffers();
    commandBuffer->addVertexBuffer(vertexBuffer->getHandle());
    commandBuffer->bindVertexBuffers();

    if (shaderProgram->getDescriptorSets()->getCount()) {
        commandBuffer->clearDescriptorSets();
        for (int i = 0; i < shaderProgram->getDescriptorSets()->getCount(); i++) {
            commandBuffer->addDescriptorSet(shaderProgram->getDescriptorSets()->at(i));
        }
        commandBuffer->bindDescriptorSets(graphicsPipeline->getBindPoint(), shaderProgram->getPipelineLayout()->getHandle());
    }

    commandBuffer->draw(vertextCount, 1, 0, 0);
}

void RaycastOctreeRenderer::draw() {
    glm::mat4 proj = glm::perspective(glm::radians(45.0f), (float)Window::get()->getWidth() / Window::get()->getHeight(), 0.1f, 100.0f);
    glm::mat4 view = glm::lookAt(glm::vec3(0, 0, 5), glm::vec3(0, 0, 0), glm::vec3(0, 1, 0));
    glm::mat4 model = glm::mat4(1.0f);
    float rot = 0;
    model = glm::rotate(model, rot, glm::vec3(0.0, 1.0, 0.0)) * glm::rotate(model, rot, glm::vec3(1.0, 1.0, 1.0));

    glm::mat4 mvp = proj * view * model;

    UBO ubo = {};
    ubo.backgroundColor = glm::vec4(0.9, 1.0, 1.0, 1.0);
    ubo.frameWidth = Window::get()->getWidth();
    ubo.frameHeight = Window::get()->getHeight();
    writeUBO(ubo);
    writeBlocks(0, blocks.data(), blocks.size() * sizeof(uint32_t));

    MetaData metaData = {};
    metaData.blockIndex = 0;
    metaData.origin = glm::vec3(0.0, 0.0, -5.0);

    glm::vec3 up = glm::vec3(0.0, -1.0, 0.0); // Flip Vulkan coordinate system by setting Y to -1
    glm::vec3 look = glm::vec3(0.0, 0.0, -1.0);
    glm::vec3 right = glm::vec3(1.0, 0.0, 0.0);

    float fov = glm::radians(50.0f);

    float width = (float)Window::get()->getWidth();
    float height = (float)Window::get()->getHeight();

    // Ray calculation is based on Johns Hopkins presentation:
    // http://www.cs.jhu.edu/~cohen/RendTech99/Lectures/Ray_Casting.bw.pdf
    glm::vec3 h0 = look - up * glm::tan(fov); // min height vector
    glm::vec3 h1 = look + up * glm::tan(fov); // max height vector
    metaData.stepH = (h1 - h0) / height;
    h0 += metaData.stepH / 2.0f;

    glm::vec3 w0 = look - right * glm::tan(fov) * width / height; // min width vector
    glm::vec3 w1 = look + right * glm::tan(fov) * width / height; // max width vector
    metaData.stepW = (w1 - w0) / width;
    w0 += metaData.stepW / 2.0f;

    metaData.startCorner = w0 + h0;

    writeMeta(0, &metaData, sizeof(MetaData));
}

void RaycastOctreeRenderer::drawView(View3D* view) {

}

void RaycastOctreeRenderer::writeUBO(const UBO& ubo) {
    uboBuffer->write(&ubo, sizeof(UBO));
}

void RaycastOctreeRenderer::writeBlocks(uint32_t offset, void* data, uint32_t size) {
    blocksBuffer->write(data, size, offset);
}

void RaycastOctreeRenderer::writeMeta(uint32_t offset, void* data, uint32_t size) {
    metaBuffer->write(data, size, offset);
}
