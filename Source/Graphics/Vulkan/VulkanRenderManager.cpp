#include "VulkanRenderManager.h"
#include "VulkanRenderWindow.h"
#include "Graphics/Vulkan/Wrapper/Instance.h"

VulkanRenderManager::VulkanRenderManager() {
    setName("VulkanRenderManager");
    vulkan = std::make_unique<Vulkan::Instance>();
    vulkan->create();
}

RenderWindow* VulkanRenderManager::createRenderWindow() {
    VulkanRenderWindow* window = new VulkanRenderWindow;
    window->create();
    vulkan->createSurface(window);
    return window;
}
