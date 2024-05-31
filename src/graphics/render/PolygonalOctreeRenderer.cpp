#include "PolygonalOctreeRenderer.h"
#include "vulkan/api/RenderPass.h"
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
#include <octree/Octree.h>

PolygonalOctreeRenderer::PolygonalOctreeRenderer(Object* parent) : OctreeRenderer(parent) {
    Vulkan::Device* device = OctreeRenderer::device();

    uint32_t startSize = 1000000; // TODO: Set optimal value or take from constant
    vertexBuffer = std::make_unique<Vulkan::GpuBuffer>(device, VK_BUFFER_USAGE_VERTEX_BUFFER_BIT, startSize);

    uboBuffer = std::make_unique<Vulkan::GpuBuffer>(device, VK_BUFFER_USAGE_UNIFORM_BUFFER_BIT, sizeof(glm::mat4));

    shaderProgram = std::make_unique<Vulkan::ShaderProgram>(device);
    shaderProgram->loadShader(ResourceManager::get()->dataPath() + "/shader/PolygonalOctree.vert.spv");
    shaderProgram->loadShader(ResourceManager::get()->dataPath() + "/shader/PolygonalOctree.frag.spv");

    VkDescriptorBufferInfo bufferInfo = {};
    bufferInfo.buffer = uboBuffer->handle();
    bufferInfo.range = VK_WHOLE_SIZE;
    shaderProgram->bindBuffer("ubo", bufferInfo);

    shaderProgram->create();

    graphicsPipeline = std::make_unique<Vulkan::GraphicsPipeline>(device);
    graphicsPipeline->setRenderPass(RenderManager::get()->renderPass()->handle());
    graphicsPipeline->setPipelineLayout(shaderProgram->pipelineLayout()->handle());

    graphicsPipeline->addDynamicState(VK_DYNAMIC_STATE_VIEWPORT);
    graphicsPipeline->addDynamicState(VK_DYNAMIC_STATE_SCISSOR);

    for (auto& shader : shaderProgram->shaders()) {
        graphicsPipeline->addShaderCode(shader->stage(), shader->code().size() * sizeof(uint32_t), shader->code().data(), "main");
    }

    VkVertexInputBindingDescription bindingDescription;
    bindingDescription.binding = 0;
    bindingDescription.stride = sizeof(Octree::Octree::Vertex);
    bindingDescription.inputRate = VK_VERTEX_INPUT_RATE_VERTEX;
    graphicsPipeline->addVertexBindingDescription(bindingDescription);

    {
        const Vulkan::Shader::LocationInfo locationInfo = shaderProgram->locationInfo("position");
        VkVertexInputAttributeDescription attributeDescription = {};
        attributeDescription.binding = bindingDescription.binding;
        attributeDescription.location = locationInfo.location;
        attributeDescription.format = locationInfo.format;
        graphicsPipeline->addVertexAttributeDescription(attributeDescription);
    }

    {
        const Vulkan::Shader::LocationInfo locationInfo = shaderProgram->locationInfo("color");
        VkVertexInputAttributeDescription attributeDescription = {};
        attributeDescription.binding = bindingDescription.binding;
        attributeDescription.location = locationInfo.location;
        attributeDescription.format = locationInfo.format;
        attributeDescription.offset = sizeof(Octree::Octree::Vertex::pos);
        graphicsPipeline->addVertexAttributeDescription(attributeDescription);
    }

    {
        const Vulkan::Shader::LocationInfo locationInfo = shaderProgram->locationInfo("normal");
        VkVertexInputAttributeDescription attributeDescription = {};
        attributeDescription.binding = bindingDescription.binding;
        attributeDescription.location = locationInfo.location;
        attributeDescription.format = locationInfo.format;
        attributeDescription.offset = sizeof(Octree::Octree::Vertex::pos) + sizeof(Octree::Octree::Vertex::color);
        graphicsPipeline->addVertexAttributeDescription(attributeDescription);
    }

    graphicsPipeline->create();
}

PolygonalOctreeRenderer::~PolygonalOctreeRenderer() {

}

void PolygonalOctreeRenderer::writeCommandBuffer(Vulkan::CommandBuffer* commandBuffer, Vulkan::Framebuffer* framebuffer [[maybe_unused]]) {
    if (vertextCount) {
        commandBuffer->bindPipeline(graphicsPipeline.get());

        commandBuffer->addVertexBuffer(vertexBuffer->handle());
        commandBuffer->bindVertexBuffers();

        for (int i = 0; i < shaderProgram->descriptorSets()->count(); i++) {
            commandBuffer->addDescriptorSet(shaderProgram->descriptorSets()->at(i));
        }
        commandBuffer->bindDescriptorSets(graphicsPipeline->bindPoint(), shaderProgram->pipelineLayout()->handle());

        commandBuffer->draw(vertextCount, 1, 0, 0);
    }
}

void PolygonalOctreeRenderer::draw() {

}

void PolygonalOctreeRenderer::drawView(View3D* view) {

}

void PolygonalOctreeRenderer::setVertexCount(uint32_t vertextCount) {
    this->vertextCount = vertextCount;

    uint32_t size = vertextCount * sizeof(Octree::Octree::Vertex);

    if (size > vertexBuffer->size()) {
        vertexBuffer = std::make_unique<Vulkan::GpuBuffer>(device(), VK_BUFFER_USAGE_VERTEX_BUFFER_BIT, size);
    }
}

void PolygonalOctreeRenderer::updateMvp(const glm::mat4& mvp) {
    uboBuffer->write(&mvp, sizeof(mvp));
}
