#include "VulkanRenderWindow.h"
#include "Graphics/Vulkan/Wrapper/Instance.h"
#include "Graphics/Vulkan/Wrapper/Surface/Surface.h"
#include "Graphics/Vulkan/Wrapper/Surface/Swapchain.h"
#include "Graphics/Vulkan/Wrapper/Queue/PresentQueue.h"
#include "Graphics/Vulkan/Wrapper/Device/PhysicalDevice.h"

#ifdef _WIN32
#include "Graphics/Vulkan/Wrapper/Surface/Win32Surface.h"
#elif __linux__
#include "Graphics/Vulkan/Wrapper/Surface/XcbSurface.h"
#endif

#include <SDL_syswm.h>

VulkanRenderWindow::VulkanRenderWindow() {

}

void VulkanRenderWindow::swapBuffers() {
    Vulkan::Instance::get()->getSurface()->getSwapchain()->getPresentQueue()->present();
    Vulkan::Instance::get()->getSurface()->getSwapchain()->acquireNextImage();
}

void VulkanRenderWindow::saveImage(const std::string& filePath) {
    Vulkan::Instance::get()->getSurface()->getSwapchain()->saveImage(filePath);
}

void VulkanRenderWindow::createSurface() {
    SDL_SysWMinfo wminfo;
    SDL_VERSION(&wminfo.version);
    SDL_GetWindowWMInfo(handle, &wminfo);

#ifdef _WIN32
    surface = std::make_shared<Win32Surface>(Vulkan::Instance::get()->getDefaultDevice()->getPhysicalDevice()->getHandle(), GetModuleHandle(nullptr), wminfo.info.win.window);
#elif __linux__
    surface = std::make_shared<Vulkan::XcbSurface>(Vulkan::Instance::get()->getDefaultDevice()->getPhysicalDevice()->getHandle(), XGetXCBConnection(wminfo.info.x11.display), wminfo.info.x11.window);
#endif

    surface->create();
    Vulkan::Instance::get()->setSurface(surface.get());
}
