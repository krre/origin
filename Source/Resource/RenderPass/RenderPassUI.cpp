#include "RenderPassUI.h"
#include "Graphics/Color.h"
#include "Core/Application.h"
#include "Core/Window.h"
#include "VulkanRenderer/API/RenderPass.h"
#include "VulkanRenderer/API/Framebuffer.h"
#include "VulkanRenderer/API/Command/CommandBuffer.h"
#include "VulkanRenderer/API/Surface/Surface.h"
#include "VulkanRenderer/API/RenderPass.h"
#include "Graphics/Render/RenderEngine.h"
#include "VulkanRenderer/ShaderProgram.h"
#include "VulkanRenderer/GpuBuffer.h"
#include "Resource/ResourceManager.h"

namespace Origin {

RenderPassUI::RenderPassUI(Vulkan::Device* device) : RenderPassResource(device) {
    renderPass = std::make_unique<Vulkan::RenderPass>(device);
    renderPass->setColorFormat(RenderEngine::get()->getSurface()->getFormats().at(0).format);
    renderPass->create();

    uint32_t startSize = 10000; // TODO: Set optimal value or take from constant
    vertexBuffer = std::make_unique<Vulkan::GpuBuffer>(VK_BUFFER_USAGE_VERTEX_BUFFER_BIT, startSize);

    Vulkan::Shader shader;
    shader.load(ResourceManager::get()->getDataPath() + "/Shader/Voxel.frag.spv");
}

RenderPassUI::~RenderPassUI() {

}

void RenderPassUI::write(Vulkan::CommandBuffer* commandBuffer, Vulkan::Framebuffer* framebuffer) {
    const Color& color = Application::get()->getWindow()->getColor();

    Vulkan::RenderPassBegin renderPassBegin(renderPass->getHandle());
    renderPassBegin.setFrameBuffer(framebuffer->getHandle());
    renderPassBegin.setRenderArea({ 0, 0, framebuffer->getWidth(), framebuffer->getHeight() });
    renderPassBegin.addClearValue({ color.getRed(), color.getGreen(), color.getBlue(), color.getAlpha() });

    commandBuffer->beginRenderPass(renderPassBegin.get());

    //    commandBuffer->bindPipeline(shaderProgram.getGraphicsPipeline());



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

void RenderPassUI::resizeVertexBuffer(uint32_t size) {
    vertexBuffer = std::make_unique<Vulkan::GpuBuffer>(VK_BUFFER_USAGE_VERTEX_BUFFER_BIT, size);
}

} // Origin
