#include "VulkanRenderer.h"
#include "VulkanRenderer/API/Command/CommandBuffer.h"
#include "VulkanRenderer/API/Framebuffer.h"
#include "VulkanRenderer/API/RenderPass.h"

namespace OctreeFarm {

VulkanRenderer::VulkanRenderer(WindowSettings windowSettings) : Vulkan::Renderer(windowSettings) {

}

VulkanRenderer::~VulkanRenderer() {

}

void VulkanRenderer::prepare() {

}

void VulkanRenderer::init() {

}

void VulkanRenderer::writeCommandBuffers(Vulkan::CommandBuffer* commandBuffer, Vulkan::Framebuffer* framebuffer) {
    getRenderPass()->setClearValue({ 0.9, 1.0, 1.0, 1.0 });
    VkRenderPassBeginInfo* beginInfo = getRenderPass()->getBeginInfo();
    beginInfo->framebuffer = framebuffer->getHandle();

    VkExtent2D extent = getSurface()->getCurrentExtent();
    beginInfo->renderArea.extent = extent;

    VkViewport viewport = {};
    viewport.width = extent.width;
    viewport.height = extent.height;
    viewport.maxDepth = 1.0;

    VkRect2D scissor = {};
    scissor.offset = { 0, 0 };
    scissor.extent = extent;

    commandBuffer->begin();

    commandBuffer->beginRenderPass(beginInfo);

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

    commandBuffer->end();
}

} // OctreeFarm
