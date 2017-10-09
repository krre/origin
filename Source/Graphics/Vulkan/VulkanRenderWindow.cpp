#include "VulkanRenderWindow.h"
#include "Graphics/Vulkan/Wrapper/Surface/Surface.h"
#include "Core/Defines.h"
#include "Graphics/Vulkan/Wrapper/Instance.h"
#include "Graphics/Vulkan/Wrapper/Surface/Swapchain.h"
#include "Graphics/Vulkan/Wrapper/Queue/PresentQueue.h"
#include "Graphics/Vulkan/Wrapper/Device/PhysicalDevice.h"

#ifdef OS_WIN
    #include "Graphics/Vulkan/Wrapper/Surface/Win32Surface.h"
#elif OS_LINUX
    #include "Graphics/Vulkan/Wrapper/Surface/XcbSurface.h"
#endif

#include <SDL_syswm.h>

VulkanRenderWindow::VulkanRenderWindow() {
    SDL_SysWMinfo wminfo;
    SDL_VERSION(&wminfo.version);
    SDL_GetWindowWMInfo(handle, &wminfo);

#ifdef OS_WIN
    surface = std::make_unique<Win32Surface>(Vulkan::Instance::get()->getDefaultDevice()->getPhysicalDevice()->getHandle(), GetModuleHandle(nullptr), wminfo.info.win.window);
#elif OS_LINUX
    surface = std::make_unique<Vulkan::XcbSurface>(Vulkan::Instance::get()->getDefaultDevice()->getPhysicalDevice()->getHandle(), XGetXCBConnection(wminfo.info.x11.display), wminfo.info.x11.window);
#endif

    surface->create();
    Vulkan::Instance::get()->setSurface(surface.get());
}

void VulkanRenderWindow::swapBuffers() {
    surface.get()->getSwapchain()->getPresentQueue()->present();
    surface.get()->getSwapchain()->acquireNextImage();
}

void VulkanRenderWindow::saveImage(const std::string& filePath) {
    surface.get()->getSwapchain()->saveImage(filePath);
}
