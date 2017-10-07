#include "VulkanRenderWindow.h"
#include "Graphics/Vulkan/Wrapper/Instance.h"
#include "Graphics/Vulkan/Wrapper/Surface.h"
#include "Graphics/Vulkan/Wrapper/Swapchain.h"
#include "Graphics/Vulkan/Wrapper/Queue/PresentQueue.h"

VulkanRenderWindow::VulkanRenderWindow() {

}

void VulkanRenderWindow::swapBuffers() {
    Vulkan::Instance::get()->getSurface()->getSwapchain()->getPresentQueue()->present();
    Vulkan::Instance::get()->getSurface()->getSwapchain()->acquireNextImage();
}

void VulkanRenderWindow::saveImage(const std::string& filePath) {
    Vulkan::Instance::get()->getSurface()->getSwapchain()->saveImage(filePath);
}
