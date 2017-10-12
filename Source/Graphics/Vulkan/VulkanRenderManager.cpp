#include "VulkanRenderManager.h"
#include "VulkanRenderWindow.h"
#include "VulkanCore.h"
#include "Graphics/Vulkan/Wrapper/Instance.h"
#include "Graphics/Vulkan/Wrapper/Device/Device.h"

VulkanRenderManager::VulkanRenderManager() {
    setName("VulkanRenderManager");
    new VulkanCore;
    vulkanInstance = std::make_unique<Vulkan::Instance>();
    vulkanInstance->create();
}

VulkanRenderManager::~VulkanRenderManager() {
    VulkanCore::get()->release();
    vulkanInstance->getDefaultDevice()->waitIdle();
}

std::shared_ptr<RenderWindow> VulkanRenderManager::createRenderWindow() {
    return std::make_shared<VulkanRenderWindow>();
}

void VulkanRenderManager::setClearColor(const Color& color) {

}

void VulkanRenderManager::clear() {

}
