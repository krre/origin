#include "RenderEngine.h"
#include "vulkan/api/command/CommandBuffer.h"
#include "vulkan/api/Framebuffer.h"
#include "vulkan/api/RenderPass.h"
// #include "vulkan/api/surface/Surface.h"
#include "vulkan/ShaderProgram.h"
#include "vulkan/GpuBuffer.h"
#include "vulkan/api/pipeline/GraphicsPipeline.h"
#include "vulkan/api/pipeline/PipelineLayout.h"
#include "vulkan/api/descriptor/DescriptorSets.h"
#include "octree/Octree.h"
#include "Viewport.h"
#include <QApplication>
#include <QDebug>

RenderEngine::RenderEngine(void* platformHandle, void* platformWindow, QObject* parent) : QObject(parent),
    Vulkan::Renderer(platformHandle, platformWindow) {
}

RenderEngine::~RenderEngine() {

}

void RenderEngine::setVoxelVertextCount(uint32_t vertexCount) {
    m_voxelRenderPass.vertextCount = vertexCount;

    uint32_t size = vertexCount * sizeof(Octree::Octree::Vertex);

    if (size > m_voxelRenderPass.vertexBuffer->size()) {
        m_voxelRenderPass.vertexBuffer.reset(new Vulkan::GpuBuffer(graphicsDevice(), VK_BUFFER_USAGE_VERTEX_BUFFER_BIT, size));
    }
}

void RenderEngine::setLineVertextCount(uint32_t vertexCount) {
    m_lineRenderPass.vertextCount = vertexCount;
}

void RenderEngine::updateMvp(const glm::mat4& mvp) {
    m_voxelUbo.mvp = mvp;
    m_lineUbo.mvp = mvp;
    updateVoxelUbo();
    m_lineRenderPass.uboBuffer->write(&m_lineUbo, sizeof(m_lineUbo));
}

void RenderEngine::updateShadeless(bool shadeless) {
    m_voxelUbo.shadeless = shadeless;
    updateVoxelUbo();
}

void RenderEngine::init() {
    initVoxelRenderPass();
    initLineRenderPass();
}

void RenderEngine::initVoxelRenderPass() {
    uint32_t startSize = 1000000; // TODO: Set optimal value or take from constant
    m_voxelRenderPass.vertexBuffer.reset(new Vulkan::GpuBuffer(graphicsDevice(), VK_BUFFER_USAGE_VERTEX_BUFFER_BIT, startSize));

    m_voxelRenderPass.uboBuffer.reset(new Vulkan::GpuBuffer(graphicsDevice(), VK_BUFFER_USAGE_UNIFORM_BUFFER_BIT, sizeof(m_voxelUbo)));

    m_voxelRenderPass.shaderProgram.reset(new Vulkan::ShaderProgram(graphicsDevice()));
    std::string shaderDataPath = QApplication::applicationDirPath().toStdString() + "/data/shader/";
    m_voxelRenderPass.shaderProgram->loadShader(shaderDataPath + "octreefarm/FrontLightOctree.vert.spv");
    m_voxelRenderPass.shaderProgram->loadShader(shaderDataPath + "octreefarm/FrontLightOctree.frag.spv");

    VkDescriptorBufferInfo bufferInfo = {};
    bufferInfo.buffer = m_voxelRenderPass.uboBuffer->handle();
    bufferInfo.range = VK_WHOLE_SIZE;
    m_voxelRenderPass.shaderProgram->bindBuffer("ubo", bufferInfo);

    m_voxelRenderPass.shaderProgram->create();

    m_voxelRenderPass. graphicsPipeline.reset(new Vulkan::GraphicsPipeline(graphicsDevice()));
    m_voxelRenderPass.graphicsPipeline->setRenderPass(renderPass()->handle());
    m_voxelRenderPass.graphicsPipeline->setPipelineLayout(m_voxelRenderPass.shaderProgram->pipelineLayout()->handle());

    m_voxelRenderPass.graphicsPipeline->addDynamicState(VK_DYNAMIC_STATE_VIEWPORT);
    m_voxelRenderPass.graphicsPipeline->addDynamicState(VK_DYNAMIC_STATE_SCISSOR);

    for (auto& shader : m_voxelRenderPass.shaderProgram->shaders()) {
        m_voxelRenderPass.graphicsPipeline->addShaderCode(shader->stage(), shader->code().size() * sizeof(uint32_t), shader->code().data(), "main");
    }

    VkVertexInputBindingDescription bindingDescription;
    bindingDescription.binding = 0;
    bindingDescription.stride = sizeof(Octree::Octree::Vertex);
    bindingDescription.inputRate = VK_VERTEX_INPUT_RATE_VERTEX;
    m_voxelRenderPass.graphicsPipeline->addVertexBindingDescription(bindingDescription);

    {
        const Vulkan::Shader::LocationInfo locationInfo = m_voxelRenderPass.shaderProgram->locationInfo("position");
        VkVertexInputAttributeDescription attributeDescription = {};
        attributeDescription.binding = bindingDescription.binding;
        attributeDescription.location = locationInfo.location;
        attributeDescription.format = locationInfo.format;
        m_voxelRenderPass.graphicsPipeline->addVertexAttributeDescription(attributeDescription);
    }

    {
        const Vulkan::Shader::LocationInfo locationInfo = m_voxelRenderPass.shaderProgram->locationInfo("color");
        VkVertexInputAttributeDescription attributeDescription = {};
        attributeDescription.binding = bindingDescription.binding;
        attributeDescription.location = locationInfo.location;
        attributeDescription.format = locationInfo.format;
        attributeDescription.offset = sizeof(Octree::Octree::Vertex::pos);
        m_voxelRenderPass.graphicsPipeline->addVertexAttributeDescription(attributeDescription);
    }

    {
        const Vulkan::Shader::LocationInfo locationInfo = m_voxelRenderPass.shaderProgram->locationInfo("normal");
        VkVertexInputAttributeDescription attributeDescription = {};
        attributeDescription.binding = bindingDescription.binding;
        attributeDescription.location = locationInfo.location;
        attributeDescription.format = locationInfo.format;
        attributeDescription.offset = sizeof(Octree::Octree::Vertex::pos) + sizeof(Octree::Octree::Vertex::color);
        m_voxelRenderPass.graphicsPipeline->addVertexAttributeDescription(attributeDescription);
    }

    m_voxelRenderPass.graphicsPipeline->create();
}

void RenderEngine::initLineRenderPass() {
    uint32_t startSize = 1000000; // TODO: Set optimal value or take from constant
    m_lineRenderPass.vertexBuffer.reset(new Vulkan::GpuBuffer(graphicsDevice(), VK_BUFFER_USAGE_VERTEX_BUFFER_BIT, startSize));

    m_lineRenderPass.uboBuffer.reset(new Vulkan::GpuBuffer(graphicsDevice(), VK_BUFFER_USAGE_UNIFORM_BUFFER_BIT, sizeof(m_lineUbo)));

    m_lineRenderPass.shaderProgram.reset(new Vulkan::ShaderProgram(graphicsDevice()));
    std::string shaderDataPath = QApplication::applicationDirPath().toStdString() + "/data/shader/";
    m_lineRenderPass.shaderProgram->loadShader(shaderDataPath + "Line.vert.spv");
    m_lineRenderPass.shaderProgram->loadShader(shaderDataPath + "Line.frag.spv");

    VkDescriptorBufferInfo bufferInfo = {};
    bufferInfo.buffer = m_lineRenderPass.uboBuffer->handle();
    bufferInfo.range = VK_WHOLE_SIZE;
    m_lineRenderPass.shaderProgram->bindBuffer("ubo", bufferInfo);

    m_lineRenderPass.shaderProgram->create();

    m_lineRenderPass. graphicsPipeline.reset(new Vulkan::GraphicsPipeline(graphicsDevice()));
    m_lineRenderPass.graphicsPipeline->setPrimitiveTopology(VK_PRIMITIVE_TOPOLOGY_LINE_LIST);
    m_lineRenderPass.graphicsPipeline->setRenderPass(renderPass()->handle());
    m_lineRenderPass.graphicsPipeline->setPipelineLayout(m_lineRenderPass.shaderProgram->pipelineLayout()->handle());

    m_lineRenderPass.graphicsPipeline->addDynamicState(VK_DYNAMIC_STATE_VIEWPORT);
    m_lineRenderPass.graphicsPipeline->addDynamicState(VK_DYNAMIC_STATE_SCISSOR);

    for (auto& shader : m_lineRenderPass.shaderProgram->shaders()) {
        m_lineRenderPass.graphicsPipeline->addShaderCode(shader->stage(), shader->code().size() * sizeof(uint32_t), shader->code().data(), "main");
    }

    VkVertexInputBindingDescription bindingDescription;
    bindingDescription.binding = 0;
    bindingDescription.stride = sizeof(Viewport::LineVertex);
    bindingDescription.inputRate = VK_VERTEX_INPUT_RATE_VERTEX;
    m_lineRenderPass.graphicsPipeline->addVertexBindingDescription(bindingDescription);

    {
        const Vulkan::Shader::LocationInfo locationInfo = m_lineRenderPass.shaderProgram->locationInfo("position");
        VkVertexInputAttributeDescription attributeDescription = {};
        attributeDescription.binding = bindingDescription.binding;
        attributeDescription.location = locationInfo.location;
        attributeDescription.format = locationInfo.format;
        m_lineRenderPass.graphicsPipeline->addVertexAttributeDescription(attributeDescription);
    }

    {
        const Vulkan::Shader::LocationInfo locationInfo = m_lineRenderPass.shaderProgram->locationInfo("color");
        VkVertexInputAttributeDescription attributeDescription = {};
        attributeDescription.binding = bindingDescription.binding;
        attributeDescription.location = locationInfo.location;
        attributeDescription.format = locationInfo.format;
        attributeDescription.offset = sizeof(Viewport::LineVertex::position);
        m_lineRenderPass.graphicsPipeline->addVertexAttributeDescription(attributeDescription);
    }

    m_lineRenderPass.graphicsPipeline->create();
}

void RenderEngine::writeCommandBuffer(Vulkan::CommandBuffer* commandBuffer, Vulkan::Framebuffer* framebuffer) {
    VkExtent2D extent = { framebuffer->width(), framebuffer->height() };

    Vulkan::RenderPassBegin renderPassBegin(renderPass()->handle());
    renderPassBegin.setFrameBuffer(framebuffer->handle());
    renderPassBegin.setRenderArea({ 0, 0, extent.width, extent.height });
    renderPassBegin.addClearValue({ 0.9f, 1.0f, 1.0f, 1.0f });
    VkClearValue depthColor = {};
    depthColor.depthStencil.depth = 1.0f;
    depthColor.depthStencil.stencil = 0.0f;
    renderPassBegin.addClearValue(depthColor);

    VkViewport viewport = {};
    viewport.width = extent.width;
    viewport.height = extent.height;
    viewport.maxDepth = 1.0;

    VkRect2D scissor = {};
    scissor.offset = { 0, 0 };
    scissor.extent = extent;

    commandBuffer->beginRenderPass(renderPassBegin.getInfo());

    if (m_voxelRenderPass.graphicsPipeline && m_voxelRenderPass.vertextCount) {
        commandBuffer->bindPipeline(m_voxelRenderPass.graphicsPipeline.data());

        commandBuffer->addViewport(viewport);
        commandBuffer->setViewport(0);

        commandBuffer->addScissor(scissor);
        commandBuffer->setScissor(0);

        commandBuffer->addVertexBuffer(m_voxelRenderPass.vertexBuffer->handle());
        commandBuffer->bindVertexBuffers();

        for (size_t i = 0; i < m_voxelRenderPass.shaderProgram->descriptorSets()->count(); i++) {
            commandBuffer->addDescriptorSet(m_voxelRenderPass.shaderProgram->descriptorSets()->at(i));
        }

        commandBuffer->bindDescriptorSets(m_voxelRenderPass.graphicsPipeline->bindPoint(), m_voxelRenderPass.shaderProgram->pipelineLayout()->handle());

        commandBuffer->draw(m_voxelRenderPass.vertextCount, 1, 0, 0);
    }

    if (m_lineRenderPass.graphicsPipeline && m_lineRenderPass.vertextCount) {
        commandBuffer->clear();

        commandBuffer->bindPipeline(m_lineRenderPass.graphicsPipeline.data());

        commandBuffer->addViewport(viewport);
        commandBuffer->setViewport(0);

        commandBuffer->addScissor(scissor);
        commandBuffer->setScissor(0);

        commandBuffer->addVertexBuffer(m_lineRenderPass.vertexBuffer->handle());
        commandBuffer->bindVertexBuffers();

        for (size_t i = 0; i < m_lineRenderPass.shaderProgram->descriptorSets()->count(); i++) {
            commandBuffer->addDescriptorSet(m_lineRenderPass.shaderProgram->descriptorSets()->at(i));
        }

        commandBuffer->bindDescriptorSets(m_lineRenderPass.graphicsPipeline->bindPoint(), m_lineRenderPass.shaderProgram->pipelineLayout()->handle());

        commandBuffer->draw(m_lineRenderPass.vertextCount, 1, 0, 0);
    }

    commandBuffer->endRenderPass();
}

void RenderEngine::updateVoxelUbo() {
    m_voxelRenderPass.uboBuffer->write(&m_voxelUbo, sizeof(m_voxelUbo));
}
