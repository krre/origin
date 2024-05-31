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
    this->voxelRenderPass.vertextCount = vertexCount;

    uint32_t size = vertexCount * sizeof(Octree::Octree::Vertex);

    if (size > voxelRenderPass.vertexBuffer->size()) {
        voxelRenderPass.vertexBuffer.reset(new Vulkan::GpuBuffer(graphicsDevice(), VK_BUFFER_USAGE_VERTEX_BUFFER_BIT, size));
    }
}

void RenderEngine::setLineVertextCount(uint32_t vertexCount) {
    this->lineRenderPass.vertextCount = vertexCount;
}

void RenderEngine::updateMvp(const glm::mat4& mvp) {
    voxelUbo.mvp = mvp;
    lineUbo.mvp = mvp;
    updateVoxelUbo();
    lineRenderPass.uboBuffer->write(&lineUbo, sizeof(lineUbo));
}

void RenderEngine::updateShadeless(bool shadeless) {
    voxelUbo.shadeless = shadeless;
    updateVoxelUbo();
}

void RenderEngine::init() {
    initVoxelRenderPass();
    initLineRenderPass();
}

void RenderEngine::initVoxelRenderPass() {
    uint32_t startSize = 1000000; // TODO: Set optimal value or take from constant
    voxelRenderPass.vertexBuffer.reset(new Vulkan::GpuBuffer(graphicsDevice(), VK_BUFFER_USAGE_VERTEX_BUFFER_BIT, startSize));

    voxelRenderPass.uboBuffer.reset(new Vulkan::GpuBuffer(graphicsDevice(), VK_BUFFER_USAGE_UNIFORM_BUFFER_BIT, sizeof(voxelUbo)));

    voxelRenderPass.shaderProgram.reset(new Vulkan::ShaderProgram(graphicsDevice()));
    std::string shaderDataPath = QApplication::applicationDirPath().toStdString() + "/data/shader/";
    voxelRenderPass.shaderProgram->loadShader(shaderDataPath + "octreefarm/FrontLightOctree.vert.spv");
    voxelRenderPass.shaderProgram->loadShader(shaderDataPath + "octreefarm/FrontLightOctree.frag.spv");

    VkDescriptorBufferInfo bufferInfo = {};
    bufferInfo.buffer = voxelRenderPass.uboBuffer->handle();
    bufferInfo.range = VK_WHOLE_SIZE;
    voxelRenderPass.shaderProgram->bindBuffer("ubo", bufferInfo);

    voxelRenderPass.shaderProgram->create();

    voxelRenderPass. graphicsPipeline.reset(new Vulkan::GraphicsPipeline(graphicsDevice()));
    voxelRenderPass.graphicsPipeline->setRenderPass(renderPass()->handle());
    voxelRenderPass.graphicsPipeline->setPipelineLayout(voxelRenderPass.shaderProgram->pipelineLayout()->handle());

    voxelRenderPass.graphicsPipeline->addDynamicState(VK_DYNAMIC_STATE_VIEWPORT);
    voxelRenderPass.graphicsPipeline->addDynamicState(VK_DYNAMIC_STATE_SCISSOR);

    for (auto& shader : voxelRenderPass.shaderProgram->shaders()) {
        voxelRenderPass.graphicsPipeline->addShaderCode(shader->stage(), shader->code().size() * sizeof(uint32_t), shader->code().data(), "main");
    }

    VkVertexInputBindingDescription bindingDescription;
    bindingDescription.binding = 0;
    bindingDescription.stride = sizeof(Octree::Octree::Vertex);
    bindingDescription.inputRate = VK_VERTEX_INPUT_RATE_VERTEX;
    voxelRenderPass.graphicsPipeline->addVertexBindingDescription(bindingDescription);

    {
        const Vulkan::Shader::LocationInfo locationInfo = voxelRenderPass.shaderProgram->locationInfo("position");
        VkVertexInputAttributeDescription attributeDescription = {};
        attributeDescription.binding = bindingDescription.binding;
        attributeDescription.location = locationInfo.location;
        attributeDescription.format = locationInfo.format;
        voxelRenderPass.graphicsPipeline->addVertexAttributeDescription(attributeDescription);
    }

    {
        const Vulkan::Shader::LocationInfo locationInfo = voxelRenderPass.shaderProgram->locationInfo("color");
        VkVertexInputAttributeDescription attributeDescription = {};
        attributeDescription.binding = bindingDescription.binding;
        attributeDescription.location = locationInfo.location;
        attributeDescription.format = locationInfo.format;
        attributeDescription.offset = sizeof(Octree::Octree::Vertex::pos);
        voxelRenderPass.graphicsPipeline->addVertexAttributeDescription(attributeDescription);
    }

    {
        const Vulkan::Shader::LocationInfo locationInfo = voxelRenderPass.shaderProgram->locationInfo("normal");
        VkVertexInputAttributeDescription attributeDescription = {};
        attributeDescription.binding = bindingDescription.binding;
        attributeDescription.location = locationInfo.location;
        attributeDescription.format = locationInfo.format;
        attributeDescription.offset = sizeof(Octree::Octree::Vertex::pos) + sizeof(Octree::Octree::Vertex::color);
        voxelRenderPass.graphicsPipeline->addVertexAttributeDescription(attributeDescription);
    }

    voxelRenderPass.graphicsPipeline->create();
}

void RenderEngine::initLineRenderPass() {
    uint32_t startSize = 1000000; // TODO: Set optimal value or take from constant
    lineRenderPass.vertexBuffer.reset(new Vulkan::GpuBuffer(graphicsDevice(), VK_BUFFER_USAGE_VERTEX_BUFFER_BIT, startSize));

    lineRenderPass.uboBuffer.reset(new Vulkan::GpuBuffer(graphicsDevice(), VK_BUFFER_USAGE_UNIFORM_BUFFER_BIT, sizeof(lineUbo)));

    lineRenderPass.shaderProgram.reset(new Vulkan::ShaderProgram(graphicsDevice()));
    std::string shaderDataPath = QApplication::applicationDirPath().toStdString() + "/data/shader/";
    lineRenderPass.shaderProgram->loadShader(shaderDataPath + "Line.vert.spv");
    lineRenderPass.shaderProgram->loadShader(shaderDataPath + "Line.frag.spv");

    VkDescriptorBufferInfo bufferInfo = {};
    bufferInfo.buffer = lineRenderPass.uboBuffer->handle();
    bufferInfo.range = VK_WHOLE_SIZE;
    lineRenderPass.shaderProgram->bindBuffer("ubo", bufferInfo);

    lineRenderPass.shaderProgram->create();

    lineRenderPass. graphicsPipeline.reset(new Vulkan::GraphicsPipeline(graphicsDevice()));
    lineRenderPass.graphicsPipeline->setPrimitiveTopology(VK_PRIMITIVE_TOPOLOGY_LINE_LIST);
    lineRenderPass.graphicsPipeline->setRenderPass(renderPass()->handle());
    lineRenderPass.graphicsPipeline->setPipelineLayout(lineRenderPass.shaderProgram->pipelineLayout()->handle());

    lineRenderPass.graphicsPipeline->addDynamicState(VK_DYNAMIC_STATE_VIEWPORT);
    lineRenderPass.graphicsPipeline->addDynamicState(VK_DYNAMIC_STATE_SCISSOR);

    for (auto& shader : lineRenderPass.shaderProgram->shaders()) {
        lineRenderPass.graphicsPipeline->addShaderCode(shader->stage(), shader->code().size() * sizeof(uint32_t), shader->code().data(), "main");
    }

    VkVertexInputBindingDescription bindingDescription;
    bindingDescription.binding = 0;
    bindingDescription.stride = sizeof(Viewport::LineVertex);
    bindingDescription.inputRate = VK_VERTEX_INPUT_RATE_VERTEX;
    lineRenderPass.graphicsPipeline->addVertexBindingDescription(bindingDescription);

    {
        const Vulkan::Shader::LocationInfo locationInfo = lineRenderPass.shaderProgram->locationInfo("position");
        VkVertexInputAttributeDescription attributeDescription = {};
        attributeDescription.binding = bindingDescription.binding;
        attributeDescription.location = locationInfo.location;
        attributeDescription.format = locationInfo.format;
        lineRenderPass.graphicsPipeline->addVertexAttributeDescription(attributeDescription);
    }

    {
        const Vulkan::Shader::LocationInfo locationInfo = lineRenderPass.shaderProgram->locationInfo("color");
        VkVertexInputAttributeDescription attributeDescription = {};
        attributeDescription.binding = bindingDescription.binding;
        attributeDescription.location = locationInfo.location;
        attributeDescription.format = locationInfo.format;
        attributeDescription.offset = sizeof(Viewport::LineVertex::position);
        lineRenderPass.graphicsPipeline->addVertexAttributeDescription(attributeDescription);
    }

    lineRenderPass.graphicsPipeline->create();
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

    if (voxelRenderPass.graphicsPipeline && voxelRenderPass.vertextCount) {
        commandBuffer->bindPipeline(voxelRenderPass.graphicsPipeline.data());

        commandBuffer->addViewport(viewport);
        commandBuffer->setViewport(0);

        commandBuffer->addScissor(scissor);
        commandBuffer->setScissor(0);

        commandBuffer->addVertexBuffer(voxelRenderPass.vertexBuffer->handle());
        commandBuffer->bindVertexBuffers();

        for (size_t i = 0; i < voxelRenderPass.shaderProgram->descriptorSets()->count(); i++) {
            commandBuffer->addDescriptorSet(voxelRenderPass.shaderProgram->descriptorSets()->at(i));
        }
        commandBuffer->bindDescriptorSets(voxelRenderPass.graphicsPipeline->bindPoint(), voxelRenderPass.shaderProgram->pipelineLayout()->handle());

        commandBuffer->draw(voxelRenderPass.vertextCount, 1, 0, 0);
    }

    if (lineRenderPass.graphicsPipeline && lineRenderPass.vertextCount) {
        commandBuffer->clear();

        commandBuffer->bindPipeline(lineRenderPass.graphicsPipeline.data());

        commandBuffer->addViewport(viewport);
        commandBuffer->setViewport(0);

        commandBuffer->addScissor(scissor);
        commandBuffer->setScissor(0);

        commandBuffer->addVertexBuffer(lineRenderPass.vertexBuffer->handle());
        commandBuffer->bindVertexBuffers();

        for (size_t i = 0; i < lineRenderPass.shaderProgram->descriptorSets()->count(); i++) {
            commandBuffer->addDescriptorSet(lineRenderPass.shaderProgram->descriptorSets()->at(i));
        }
        commandBuffer->bindDescriptorSets(lineRenderPass.graphicsPipeline->bindPoint(), lineRenderPass.shaderProgram->pipelineLayout()->handle());

        commandBuffer->draw(lineRenderPass.vertextCount, 1, 0, 0);
    }

    commandBuffer->endRenderPass();
}

void RenderEngine::updateVoxelUbo() {
    voxelRenderPass.uboBuffer->write(&voxelUbo, sizeof(voxelUbo));
}
