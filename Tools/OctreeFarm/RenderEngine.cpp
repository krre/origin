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
#include <QApplication>

namespace OctreeFarm {

RenderEngine::RenderEngine(void* platformHandle, void* platformWindow, QObject* parent) :
    QObject(parent),
    Vulkan::Renderer(platformHandle, platformWindow) {

}

RenderEngine::~RenderEngine() {

}

void RenderEngine::init() {
    uint32_t startSize = 1000000; // TODO: Set optimal value or take from constant
    vertexBuffer.reset(new Vulkan::GpuBuffer(getGraphicsDevice(), VK_BUFFER_USAGE_VERTEX_BUFFER_BIT, startSize));

    uboBuffer.reset(new Vulkan::GpuBuffer(getGraphicsDevice(), VK_BUFFER_USAGE_UNIFORM_BUFFER_BIT, sizeof(glm::mat4)));

    shaderProgram.reset(new Vulkan::ShaderProgram(getGraphicsDevice()));
    std::string shaderDataPath = QApplication::applicationDirPath().toStdString() + "/Data/Shader";
    shaderProgram->loadShader(shaderDataPath + "/Voxel.vert.spv");
    shaderProgram->loadShader(shaderDataPath + "/Voxel.frag.spv");

    VkDescriptorBufferInfo bufferInfo = {};
    bufferInfo.buffer = uboBuffer->getHandle();
    bufferInfo.range = VK_WHOLE_SIZE;
    shaderProgram->bindBuffer("ubo", bufferInfo);

    shaderProgram->create();

    graphicsPipeline.reset(new Vulkan::GraphicsPipeline(getGraphicsDevice()));
    graphicsPipeline->setRenderPass(getRenderPass()->getHandle());
    graphicsPipeline->setPipelineLayout(shaderProgram->getPipelineLayout()->getHandle());

    graphicsPipeline->addDynamicState(VK_DYNAMIC_STATE_VIEWPORT);
    graphicsPipeline->addDynamicState(VK_DYNAMIC_STATE_SCISSOR);

    for (auto& shader : shaderProgram->getShaders()) {
        graphicsPipeline->addShaderCode(shader->getStage(), shader->getCode().size() * sizeof(uint32_t), shader->getCode().data(), "main");
    }

    VkVertexInputBindingDescription bindingDescription;
    bindingDescription.binding = 0;
    bindingDescription.stride = sizeof(Vertex);
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

    {
        const Vulkan::Shader::LocationInfo locationInfo = shaderProgram->getLocationInfo("color");
        VkVertexInputAttributeDescription attributeDescription = {};
        attributeDescription.binding = bindingDescription.binding;
        attributeDescription.location = locationInfo.location;
        attributeDescription.format = locationInfo.format;
        attributeDescription.offset = sizeof(Vertex::pos);
        graphicsPipeline->addVertexAttributeDescription(attributeDescription);
    }

    graphicsPipeline->create();
}

void RenderEngine::writeCommandBuffers(Vulkan::CommandBuffer* commandBuffer, Vulkan::Framebuffer* framebuffer) {
    VkExtent2D extent = { framebuffer->getWidth(), framebuffer->getHeight() };

    Vulkan::RenderPassBegin renderPassBegin(getRenderPass()->getHandle());
    renderPassBegin.setFrameBuffer(framebuffer->getHandle());
    renderPassBegin.setRenderArea({ 0, 0, extent.width, extent.height });
    renderPassBegin.addClearValue({ 0.9, 1.0, 1.0, 1.0 });

    VkViewport viewport = {};
    viewport.width = extent.width;
    viewport.height = extent.height;
    viewport.maxDepth = 1.0;

    VkRect2D scissor = {};
    scissor.offset = { 0, 0 };
    scissor.extent = extent;

    commandBuffer->beginRenderPass(renderPassBegin.getInfo());

    if (graphicsPipeline && vertextCount) {
        commandBuffer->bindPipeline(graphicsPipeline.data());

        commandBuffer->addViewport(viewport);
        commandBuffer->setViewport(0);

        commandBuffer->addScissor(scissor);
        commandBuffer->setScissor(0);

        commandBuffer->addVertexBuffer(vertexBuffer->getHandle());
        commandBuffer->bindVertexBuffers();

        for (size_t i = 0; i < shaderProgram->getDescriptorSets()->getCount(); i++) {
            commandBuffer->addDescriptorSet(shaderProgram->getDescriptorSets()->at(i));
        }
        commandBuffer->bindDescriptorSets(graphicsPipeline->getBindPoint(), shaderProgram->getPipelineLayout()->getHandle());

        commandBuffer->draw(vertextCount, 1, 0, 0);
    }

    commandBuffer->endRenderPass();
}

} // OctreeFarm
