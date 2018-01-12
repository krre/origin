#include "VulkanRenderer.h"
#include "Graphics/Render/RenderManager.h"
#include "Core/Application.h"
#include "Graphics/Vulkan/Wrapper/Semaphore.h"
#include "Graphics/Vulkan/Wrapper/Queue/SubmitQueue.h"
#include "Graphics/Vulkan/Wrapper/Command/CommandBuffers.h"
#include "Graphics/Vulkan/Wrapper/Command/CommandBuffer.h"
#include "Graphics/Vulkan/Wrapper/Surface/Swapchain.h"
#include "Graphics/Vulkan/VulkanRenderContext.h"
#include "Graphics/Vulkan/VulkanRenderWindow.h"

namespace Origin {

VulkanRenderer::VulkanRenderer() {
    device = vkCtx->getGraphicsDevice();
    window = static_cast<VulkanRenderWindow*>(Application::get()->getWindow());

    commandBufferHandlers = std::make_unique<Vulkan::CommandBuffers>(device, vkCtx->getGraphicsCommandPool());
    commandBufferHandlers->allocate(window->getSwapchain()->getCount());

    for (int i = 0; i < commandBufferHandlers->getCount(); i++) {
        auto commandBuffer = std::make_unique<Vulkan::CommandBuffer>(commandBufferHandlers->at(i));
        commandBuffers.push_back(std::move(commandBuffer));
    }

    submitQueue = std::make_unique<Vulkan::SubmitQueue>(device, vkCtx->getGraphicsFamily());
    submitQueue->create();
}

VulkanRenderer::~VulkanRenderer() {
    submitQueue->waitIdle();
}

void VulkanRenderer::renderQueue() {
    submitQueue->clearWaitSemaphores();
    submitQueue->addWaitSemaphore(window->getImageAvailableSemaphore());

    submitQueue->clearCommandBuffers();
    submitQueue->addCommandBuffer(commandBuffers.at(window->getImageIndex()).get(),
                                  window->getImageAvailableSemaphore(), VK_PIPELINE_STAGE_ALL_GRAPHICS_BIT, window->getRenderFinishedSemaphore());
    submitQueue->submit();
}

} // Origin
