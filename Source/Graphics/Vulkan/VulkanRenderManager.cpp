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

RenderWindow* VulkanRenderManager::createRenderWindow() {
    VulkanRenderWindow* window = new VulkanRenderWindow;
    window->create();
    window->createSurface();
    return window;
}
