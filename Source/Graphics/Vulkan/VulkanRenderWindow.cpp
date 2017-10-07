#include "VulkanRenderWindow.h"
#include "Graphics/Vulkan/Wrapper/Instance.h"
#include "Graphics/Vulkan/Wrapper/Surface.h"
#include "Graphics/Vulkan/Wrapper/Swapchain.h"

VulkanRenderWindow::VulkanRenderWindow() {

}

void VulkanRenderWindow::swapBuffers() {

}

void VulkanRenderWindow::saveImage(const std::string& filePath) {
    Vulkan::Instance::get()->getSurface()->getSwapchain()->saveImage(filePath);
}
