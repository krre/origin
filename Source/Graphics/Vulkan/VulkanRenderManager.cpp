#include "VulkanRenderManager.h"
#include "VulkanRenderWindow.h"
#include "VulkanCore.h"

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
