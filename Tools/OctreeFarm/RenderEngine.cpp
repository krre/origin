#include "RenderEngine.h"
#include "Vulkan/API/Command/CommandBuffer.h"
#include "Vulkan/API/Framebuffer.h"
#include "Vulkan/API/RenderPass.h"
#include "Vulkan/API/Surface/Surface.h"

namespace OctreeFarm {

RenderEngine::RenderEngine(void* platformHandle, void* platformWindow, QObject* parent) :
    QObject(parent),
    Vulkan::Renderer(platformHandle, platformWindow) {

}

RenderEngine::~RenderEngine() {

}

void RenderEngine::init() {

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

    //    commandBuffer->bindPipeline(shaderProgram.getGraphicsPipeline());

    commandBuffer->addViewport(viewport);
    commandBuffer->setViewport(0);

    commandBuffer->addScissor(scissor);
    commandBuffer->setScissor(0);

    //    commandBuffer->addVertexBuffer(vertexBuffer->getHandle());
    //    commandBuffer->bindVertexBuffers();
    //    commandBuffer->bindIndexBuffer(indexBuffer->getHandle(), indexBuffer->getIndexType());

    //    for (int i = 0; i < shaderProgram.getDescriptorSets()->getCount(); i++) {
    //        commandBuffer->addDescriptorSet(shaderProgram.getDescriptorSets()->at(i));
    //    }
    //    commandBuffer->bindDescriptorSets(shaderProgram.getGraphicsPipeline()->getBindPoint(), shaderProgram.getPipelineLayout()->getHandle());
    //    commandBuffer->drawIndexed(MAX_CHAR_COUNT, 1, 0, 0, 0);

    commandBuffer->endRenderPass();
}

} // OctreeFarm
