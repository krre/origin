#include "RenderEngine.h"
#include "Vulkan/API/Command/CommandBuffer.h"
#include "Vulkan/API/Framebuffer.h"
#include "Vulkan/API/RenderPass.h"
#include "Vulkan/API/Surface/Surface.h"
#include "Vulkan/ShaderProgram.h"
#include "Vulkan/GpuBuffer.h"
#include "Vulkan/API/Pipeline/GraphicsPipeline.h"
#include "Vulkan/API/Pipeline/PipelineLayout.h"
#include "Vulkan/API/Descriptor/DescriptorSets.h"
#include "Octree/Octree.h"
#include <QApplication>

namespace OctreeFarm {

RenderEngine::RenderEngine(void* platformHandle, void* platformWindow, QObject* parent) :
    QObject(parent),
    Vulkan::Renderer(platformHandle, platformWindow) {

}

RenderEngine::~RenderEngine() {

}

void RenderEngine::setVertextCount(uint32_t vertexCount) {
    this->voxelRenderPass.vertextCount = vertexCount;

    uint32_t size = vertexCount * sizeof(Origin::Octree::Vertex);

    if (size > voxelRenderPass.vertexBuffer->getSize()) {
        voxelRenderPass.vertexBuffer.reset(new Vulkan::GpuBuffer(getGraphicsDevice(), VK_BUFFER_USAGE_VERTEX_BUFFER_BIT, size));
    }
}

void RenderEngine::updateMvp(const glm::mat4& mvp) {
    voxelUbo.mvp = mvp;
    updateUBO();
}

void RenderEngine::updateShadeless(bool shadeless) {
    voxelUbo.shadeless = shadeless;
    updateUBO();
}

void RenderEngine::init() {
    uint32_t startSize = 1000000; // TODO: Set optimal value or take from constant
    voxelRenderPass.vertexBuffer.reset(new Vulkan::GpuBuffer(getGraphicsDevice(), VK_BUFFER_USAGE_VERTEX_BUFFER_BIT, startSize));

    voxelRenderPass.uboBuffer.reset(new Vulkan::GpuBuffer(getGraphicsDevice(), VK_BUFFER_USAGE_UNIFORM_BUFFER_BIT, sizeof(voxelUbo)));

    voxelRenderPass.shaderProgram.reset(new Vulkan::ShaderProgram(getGraphicsDevice()));
    std::string shaderDataPath = QApplication::applicationDirPath().toStdString() + "/Data/Shader/";
    voxelRenderPass.shaderProgram->loadShader(shaderDataPath + "OctreeFarm/FrontLightOctree.vert.spv");
    voxelRenderPass.shaderProgram->loadShader(shaderDataPath + "OctreeFarm/FrontLightOctree.frag.spv");

    VkDescriptorBufferInfo bufferInfo = {};
    bufferInfo.buffer = voxelRenderPass.uboBuffer->getHandle();
    bufferInfo.range = VK_WHOLE_SIZE;
    voxelRenderPass.shaderProgram->bindBuffer("ubo", bufferInfo);

    voxelRenderPass.shaderProgram->create();

    voxelRenderPass. graphicsPipeline.reset(new Vulkan::GraphicsPipeline(getGraphicsDevice()));
    voxelRenderPass.graphicsPipeline->setRenderPass(getRenderPass()->getHandle());
    voxelRenderPass.graphicsPipeline->setPipelineLayout(voxelRenderPass.shaderProgram->getPipelineLayout()->getHandle());

    voxelRenderPass.graphicsPipeline->addDynamicState(VK_DYNAMIC_STATE_VIEWPORT);
    voxelRenderPass.graphicsPipeline->addDynamicState(VK_DYNAMIC_STATE_SCISSOR);

    for (auto& shader : voxelRenderPass.shaderProgram->getShaders()) {
        voxelRenderPass.graphicsPipeline->addShaderCode(shader->getStage(), shader->getCode().size() * sizeof(uint32_t), shader->getCode().data(), "main");
    }

    VkVertexInputBindingDescription bindingDescription;
    bindingDescription.binding = 0;
    bindingDescription.stride = sizeof(Origin::Octree::Vertex);
    bindingDescription.inputRate = VK_VERTEX_INPUT_RATE_VERTEX;
    voxelRenderPass.graphicsPipeline->addVertexBindingDescription(bindingDescription);

    {
        const Vulkan::Shader::LocationInfo locationInfo = voxelRenderPass.shaderProgram->getLocationInfo("position");
        VkVertexInputAttributeDescription attributeDescription = {};
        attributeDescription.binding = bindingDescription.binding;
        attributeDescription.location = locationInfo.location;
        attributeDescription.format = locationInfo.format;
        voxelRenderPass.graphicsPipeline->addVertexAttributeDescription(attributeDescription);
    }

    {
        const Vulkan::Shader::LocationInfo locationInfo = voxelRenderPass.shaderProgram->getLocationInfo("color");
        VkVertexInputAttributeDescription attributeDescription = {};
        attributeDescription.binding = bindingDescription.binding;
        attributeDescription.location = locationInfo.location;
        attributeDescription.format = locationInfo.format;
        attributeDescription.offset = sizeof(Origin::Octree::Vertex::pos);
        voxelRenderPass.graphicsPipeline->addVertexAttributeDescription(attributeDescription);
    }

    {
        const Vulkan::Shader::LocationInfo locationInfo = voxelRenderPass.shaderProgram->getLocationInfo("normal");
        VkVertexInputAttributeDescription attributeDescription = {};
        attributeDescription.binding = bindingDescription.binding;
        attributeDescription.location = locationInfo.location;
        attributeDescription.format = locationInfo.format;
        attributeDescription.offset = sizeof(Origin::Octree::Vertex::pos) + sizeof(Origin::Octree::Vertex::color);
        voxelRenderPass.graphicsPipeline->addVertexAttributeDescription(attributeDescription);
    }

    voxelRenderPass.graphicsPipeline->create();
}

void RenderEngine::writeCommandBuffers(Vulkan::CommandBuffer* commandBuffer, Vulkan::Framebuffer* framebuffer) {
    VkExtent2D extent = { framebuffer->getWidth(), framebuffer->getHeight() };

    Vulkan::RenderPassBegin renderPassBegin(getRenderPass()->getHandle());
    renderPassBegin.setFrameBuffer(framebuffer->getHandle());
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

        commandBuffer->addVertexBuffer(voxelRenderPass.vertexBuffer->getHandle());
        commandBuffer->bindVertexBuffers();

        for (size_t i = 0; i < voxelRenderPass.shaderProgram->getDescriptorSets()->getCount(); i++) {
            commandBuffer->addDescriptorSet(voxelRenderPass.shaderProgram->getDescriptorSets()->at(i));
        }
        commandBuffer->bindDescriptorSets(voxelRenderPass.graphicsPipeline->getBindPoint(), voxelRenderPass.shaderProgram->getPipelineLayout()->getHandle());

        commandBuffer->draw(voxelRenderPass.vertextCount, 1, 0, 0);
    }

    commandBuffer->endRenderPass();
}

void RenderEngine::updateUBO() {
    voxelRenderPass.uboBuffer->write(&voxelUbo, sizeof(voxelUbo));
}

} // OctreeFarm
