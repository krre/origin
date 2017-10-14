#include "VulkanRenderManager.h"
#include "VulkanCore.h"
#include "VulkanRenderWindow.h"

#include "Graphics/Vulkan/Wrapper/Surface/Surface.h"
#include "Graphics/Vulkan/Wrapper/Surface/Swapchain.h"
#include "Graphics/Vulkan/Wrapper/Image/ImageView.h"
#include "Graphics/Vulkan/Wrapper/Framebuffer.h"
#include "Graphics/Vulkan/Wrapper/Semaphore.h"
#include "Graphics/Vulkan/Wrapper/RenderPass.h"
#include "Graphics/Vulkan/Wrapper/Queue/PresentQueue.h"

VulkanRenderManager::VulkanRenderManager() {
    setName("VulkanRenderManager");
    new VulkanCore;
}

VulkanRenderManager::~VulkanRenderManager() {
    VulkanCore::get()->release();
}

std::shared_ptr<RenderWindow> VulkanRenderManager::createRenderWindow() {
    return std::make_shared<VulkanRenderWindow>();
}
