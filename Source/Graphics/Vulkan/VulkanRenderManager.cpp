#include "VulkanRenderManager.h"
#include "VulkanRenderWindow.h"
#include "Graphics/Vulkan/Wrapper/Instance.h"

VulkanRenderManager::VulkanRenderManager() {
    setName("VulkanRenderManager");
    vulkan = std::make_unique<Vulkan::Instance>();
}

RenderWindow* VulkanRenderManager::createRenderWindow() {
    VulkanRenderWindow* window = new VulkanRenderWindow;
    window->create();
    vulkan->create();
    vulkan->createSurface(window);
    return window;
}
