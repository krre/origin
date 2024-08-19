#include "RaycastOctreeRenderer.h"
#include "graphics/render/RenderManager.h"
#include "base/Window.h"
#include "vulkan/api/Framebuffer.h"
#include "vulkan/api/command/CommandBuffer.h"
#include "vulkan/api/RenderPass.h"
#include "vulkan/api/descriptor/DescriptorSets.h"
#include "vulkan/api/pipeline/PipelineLayout.h"
#include "graphics/render/RenderManager.h"
#include "vulkan/ShaderProgram.h"
#include "vulkan/GpuBuffer.h"
#include "vulkan/api/pipeline/GraphicsPipeline.h"
#include "resource/ResourceManager.h"
#include <glm/gtc/matrix_transform.hpp>

RaycastOctreeRenderer::RaycastOctreeRenderer(Object* parent) : OctreeRenderer(parent) {
    std::vector<glm::vec2> plane = {
       { -1.0, 1.0 }, { -1.0, -1.0 }, { 1.0, -1.0 },
        { -1.0, 1.0 }, { 1.0, -1.0 }, { 1.0, 1.0 }
    };

    Vulkan::Device* device = OctreeRenderer::device();

    m_vertextCount = plane.size();

    int size = plane.size() * sizeof(glm::vec2);
    m_vertexBuffer = std::make_unique<Vulkan::GpuBuffer>(device, VK_BUFFER_USAGE_VERTEX_BUFFER_BIT, size);
    m_vertexBuffer->write(plane.data(), size);

    m_shaderProgram = std::make_unique<Vulkan::ShaderProgram>(device);
    m_shaderProgram->loadShader(ResourceManager::get()->dataPath() + "/shader/RaycastOctree.vert.spv");
    m_shaderProgram->loadShader(ResourceManager::get()->dataPath() + "/shader/RaycastOctree.frag.spv");

    m_uboBuffer = std::make_unique<Vulkan::GpuBuffer>(device, VK_BUFFER_USAGE_UNIFORM_BUFFER_BIT, sizeof(UBO));

    VkDescriptorBufferInfo bufferInfo = {};
    bufferInfo.buffer = m_uboBuffer->handle();
    bufferInfo.range = VK_WHOLE_SIZE;
    m_shaderProgram->bindBuffer("ubo", bufferInfo);

    m_blocksBuffer = std::make_unique<Vulkan::GpuBuffer>(device, VK_BUFFER_USAGE_STORAGE_BUFFER_BIT, 1000000); // TODO: Use size from constant

    bufferInfo.buffer = m_blocksBuffer->handle();
    bufferInfo.range = VK_WHOLE_SIZE;
    m_shaderProgram->bindBuffer("blocks", bufferInfo);

    m_metaBuffer = std::make_unique<Vulkan::GpuBuffer>(device, VK_BUFFER_USAGE_STORAGE_BUFFER_BIT, 100000); // TODO: Use size from constant

    bufferInfo.buffer = m_metaBuffer->handle();
    bufferInfo.range = VK_WHOLE_SIZE;
    m_shaderProgram->bindBuffer("meta", bufferInfo);

    m_shaderProgram->create();

    m_graphicsPipeline = std::make_unique<Vulkan::GraphicsPipeline>(device);
    m_graphicsPipeline->setRenderPass(RenderManager::get()->renderPass()->handle());
    m_graphicsPipeline->setPipelineLayout(m_shaderProgram->pipelineLayout()->handle());

    m_graphicsPipeline->addDynamicState(VK_DYNAMIC_STATE_VIEWPORT);
    m_graphicsPipeline->addDynamicState(VK_DYNAMIC_STATE_SCISSOR);

    for (auto& shader : m_shaderProgram->shaders()) {
        m_graphicsPipeline->addShaderCode(shader->stage(), shader->code().size() * sizeof(uint32_t), shader->code().data(), "main");
    }

    VkVertexInputBindingDescription bindingDescription;
    bindingDescription.binding = 0;
    bindingDescription.stride = sizeof(glm::vec2);
    bindingDescription.inputRate = VK_VERTEX_INPUT_RATE_VERTEX;
    m_graphicsPipeline->addVertexBindingDescription(bindingDescription);

    {
        const Vulkan::Shader::LocationInfo locationInfo = m_shaderProgram->locationInfo("position");
        VkVertexInputAttributeDescription attributeDescription = {};
        attributeDescription.binding = bindingDescription.binding;
        attributeDescription.location = locationInfo.location;
        attributeDescription.format = locationInfo.format;
        m_graphicsPipeline->addVertexAttributeDescription(attributeDescription);
    }

    m_graphicsPipeline->create();

    m_blocks.push_back(0xFF0000FF);
}

RaycastOctreeRenderer::~RaycastOctreeRenderer() {

}

void RaycastOctreeRenderer::writeCommandBuffer(Vulkan::CommandBuffer* commandBuffer, Vulkan::Framebuffer* framebuffer [[maybe_unused]]) {
    commandBuffer->bindPipeline(m_graphicsPipeline.get());

    commandBuffer->clearVertexBuffers();
    commandBuffer->addVertexBuffer(m_vertexBuffer->handle());
    commandBuffer->bindVertexBuffers();

    if (m_shaderProgram->descriptorSets()->count()) {
        commandBuffer->clearDescriptorSets();
        for (int i = 0; i < m_shaderProgram->descriptorSets()->count(); i++) {
            commandBuffer->addDescriptorSet(m_shaderProgram->descriptorSets()->at(i));
        }
        commandBuffer->bindDescriptorSets(m_graphicsPipeline->bindPoint(), m_shaderProgram->pipelineLayout()->handle());
    }

    commandBuffer->draw(m_vertextCount, 1, 0, 0);
}

void RaycastOctreeRenderer::draw() {
    glm::mat4 proj = glm::perspective(glm::radians(45.0f), (float)Window::get()->width() / Window::get()->height(), 0.1f, 100.0f);
    glm::mat4 view = glm::lookAt(glm::vec3(0, 0, 5), glm::vec3(0, 0, 0), glm::vec3(0, 1, 0));
    glm::mat4 model = glm::mat4(1.0f);
    float rot = 0;
    model = glm::rotate(model, rot, glm::vec3(0.0, 1.0, 0.0)) * glm::rotate(model, rot, glm::vec3(1.0, 1.0, 1.0));

    glm::mat4 mvp = proj * view * model;

    UBO ubo = {};
    ubo.backgroundColor = glm::vec4(0.9, 1.0, 1.0, 1.0);
    ubo.frameWidth = Window::get()->width();
    ubo.frameHeight = Window::get()->height();
    writeUBO(ubo);
    writeBlocks(0, m_blocks.data(), m_blocks.size() * sizeof(uint32_t));

    MetaData metaData = {};
    metaData.blockIndex = 0;
    metaData.origin = glm::vec3(0.0, 0.0, -5.0);

    glm::vec3 up = glm::vec3(0.0, -1.0, 0.0); // Flip Vulkan coordinate system by setting Y to -1
    glm::vec3 look = glm::vec3(0.0, 0.0, -1.0);
    glm::vec3 right = glm::vec3(1.0, 0.0, 0.0);

    float fov = glm::radians(50.0f);

    float width = (float)Window::get()->width();
    float height = (float)Window::get()->height();

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
    m_uboBuffer->write(&ubo, sizeof(UBO));
}

void RaycastOctreeRenderer::writeBlocks(uint32_t offset, void* data, uint32_t size) {
    m_blocksBuffer->write(data, size, offset);
}

void RaycastOctreeRenderer::writeMeta(uint32_t offset, void* data, uint32_t size) {
    m_metaBuffer->write(data, size, offset);
}
