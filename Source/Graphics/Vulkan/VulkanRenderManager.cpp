#include "VulkanRenderManager.h"
#include "VulkanRenderWindow.h"

VulkanRenderManager::VulkanRenderManager() {
    setName("VulkanRenderManager");
}

RenderWindow* VulkanRenderManager::createRenderWindow() {
    return new VulkanRenderWindow;
}
