#include "DebugRenderer.h"
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

static DebugRenderer* instance = nullptr;

DebugRenderer::DebugRenderer(Object* parent) : Renderer(parent) {
    instance = this;
    setActive(false);

    Vulkan::Device* device = Renderer::device();

    uint32_t startSize = 1000000; // TODO: Set optimal value or take from constant
    m_vertexBuffer = std::make_unique<Vulkan::GpuBuffer>(device, VK_BUFFER_USAGE_VERTEX_BUFFER_BIT, startSize);

    m_uboBuffer = std::make_unique<Vulkan::GpuBuffer>(device, VK_BUFFER_USAGE_UNIFORM_BUFFER_BIT, sizeof(glm::mat4));

    m_shaderProgram = std::make_unique<Vulkan::ShaderProgram>(device);
    m_shaderProgram->loadShader(ResourceManager::get()->dataPath() + "/shader/PolygonalOctree.vert.spv");
    m_shaderProgram->loadShader(ResourceManager::get()->dataPath() + "/shader/PolygonalOctree.frag.spv");

    VkDescriptorBufferInfo bufferInfo = {};
    bufferInfo.buffer = m_uboBuffer->handle();
    bufferInfo.range = VK_WHOLE_SIZE;
    m_shaderProgram->bindBuffer("ubo", bufferInfo);

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
    bindingDescription.stride = sizeof(Octree::Octree::Vertex);
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

    {
        const Vulkan::Shader::LocationInfo locationInfo = m_shaderProgram->locationInfo("color");
        VkVertexInputAttributeDescription attributeDescription = {};
        attributeDescription.binding = bindingDescription.binding;
        attributeDescription.location = locationInfo.location;
        attributeDescription.format = locationInfo.format;
        attributeDescription.offset = sizeof(Octree::Octree::Vertex::pos);
        m_graphicsPipeline->addVertexAttributeDescription(attributeDescription);
    }

    {
        const Vulkan::Shader::LocationInfo locationInfo = m_shaderProgram->locationInfo("normal");
        VkVertexInputAttributeDescription attributeDescription = {};
        attributeDescription.binding = bindingDescription.binding;
        attributeDescription.location = locationInfo.location;
        attributeDescription.format = locationInfo.format;
        attributeDescription.offset = sizeof(Octree::Octree::Vertex::pos) + sizeof(Octree::Octree::Vertex::color);
        m_graphicsPipeline->addVertexAttributeDescription(attributeDescription);
    }

    m_graphicsPipeline->create();
}

DebugRenderer::~DebugRenderer() {

}

void DebugRenderer::writeCommandBuffer(Vulkan::CommandBuffer* commandBuffer, Vulkan::Framebuffer* framebuffer [[maybe_unused]]) {
    if (m_vertextCount) {
        commandBuffer->bindPipeline(m_graphicsPipeline.get());

        commandBuffer->addVertexBuffer(m_vertexBuffer->handle());
        commandBuffer->bindVertexBuffers();

        for (int i = 0; i < m_shaderProgram->descriptorSets()->count(); i++) {
            commandBuffer->addDescriptorSet(m_shaderProgram->descriptorSets()->at(i));
        }
        commandBuffer->bindDescriptorSets(m_graphicsPipeline->bindPoint(), m_shaderProgram->pipelineLayout()->handle());

        commandBuffer->draw(m_vertextCount, 1, 0, 0);
    }
}

DebugRenderer* DebugRenderer::get() {
    return instance;
}

void DebugRenderer::draw() {

}

void DebugRenderer::setVertexCount(uint32_t vertextCount) {
    this->m_vertextCount = vertextCount;

    uint32_t size = vertextCount * sizeof(Octree::Octree::Vertex);

    if (size > m_vertexBuffer->size()) {
        m_vertexBuffer = std::make_unique<Vulkan::GpuBuffer>(device(), VK_BUFFER_USAGE_VERTEX_BUFFER_BIT, size);
    }
}

void DebugRenderer::updateMvp(const glm::mat4& mvp) {
    m_uboBuffer->write(&mvp, sizeof(mvp));
}
