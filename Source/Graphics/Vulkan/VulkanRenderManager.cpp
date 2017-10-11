#include "VulkanRenderManager.h"
#include "VulkanRenderWindow.h"
#include "Graphics/Vulkan/Wrapper/Instance.h"
#include "Graphics/Vulkan/Wrapper/Device/Device.h"

VulkanRenderManager::VulkanRenderManager() {
    setName("VulkanRenderManager");
    vulkanInstance = std::make_unique<Vulkan::Instance>();
    vulkanInstance->create();
}

VulkanRenderManager::~VulkanRenderManager() {
    vulkanInstance->getDefaultDevice()->waitIdle();
}

std::shared_ptr<RenderWindow> VulkanRenderManager::createRenderWindow() {
    return std::make_shared<VulkanRenderWindow>();
}

void VulkanRenderManager::setClearColor(const Color& color) {

}

void VulkanRenderManager::clear() {

}
