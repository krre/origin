#include "VulkanRenderManager.h"
#include "VulkanRenderWindow.h"
#include "Graphics/Vulkan/Wrapper/Instance.h"
#include "Graphics/Vulkan/Wrapper/Device/Device.h"

VulkanRenderManager::VulkanRenderManager() {
    setName("VulkanRenderManager");
    vulkan = std::make_unique<Vulkan::Instance>();
    vulkan->create();
}

VulkanRenderManager::~VulkanRenderManager() {
    vulkan->getDefaultDevice()->waitIdle();
}

std::shared_ptr<RenderWindow> VulkanRenderManager::createRenderWindow() {
    return std::make_shared<VulkanRenderWindow>();
}
