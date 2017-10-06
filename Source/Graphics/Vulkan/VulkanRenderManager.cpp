#include "VulkanRenderManager.h"
#include "VulkanRenderWindow.h"

VulkanRenderManager::VulkanRenderManager() {

}

RenderWindow* VulkanRenderManager::createRenderWindow() {
    return new VulkanRenderWindow;
}
