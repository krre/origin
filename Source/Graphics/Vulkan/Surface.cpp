#include "Surface.h"
#include "Instance.h"
#include "Core/App.h"
#include "Core/GameWindow.h"
#include "Swapchain.h"
#include <SDL_syswm.h>
#ifdef __linux__
    #include <X11/Xlib-xcb.h>
#elif _WIN32

#endif

using namespace Vulkan;

Surface::Surface(VkPhysicalDevice physicalDevice) :
    physicalDevice(physicalDevice) {
}

Surface::~Surface() {
    swapchain.reset();
    destroy();
}

void Surface::create() {
    SDL_SysWMinfo wminfo;
    SDL_VERSION(&wminfo.version);
    SDL_GetWindowWMInfo(App::get()->getWindow()->getHandle(), &wminfo);

    switch (wminfo.subsystem) {
#ifdef __linux__
    case SDL_SYSWM_X11: {
        VkXcbSurfaceCreateInfoKHR createInfo = {};
        createInfo.sType = VK_STRUCTURE_TYPE_XCB_SURFACE_CREATE_INFO_KHR;
        createInfo.flags = 0;
        createInfo.connection = XGetXCBConnection(wminfo.info.x11.display);
        createInfo.window = wminfo.info.x11.window;
        VULKAN_CHECK_RESULT(vkCreateXcbSurfaceKHR(Instance::get()->getHandle(), &createInfo, nullptr, &handle), "Failed to create Xcb surface");
        break;
    }
#elif _WIN32
    case SDL_SYSWM_WINDOWS: {
        VkWin32SurfaceCreateInfoKHR createInfo = {};
        createInfo.sType = VK_STRUCTURE_TYPE_WIN32_SURFACE_CREATE_INFO_KHR;
        createInfo.flags = 0;
        createInfo.hwnd = wminfo.info.win.window;
        createInfo.hinstance = GetModuleHandle(nullptr);
        VULKAN_CHECK_RESULT(vkCreateWin32SurfaceKHR(Instance::get()->getHandle(), &createInfo, nullptr, &handle), "Failed to create win32 surface");
        break;
    }
#endif
    }

    uint32_t count;
    vkGetPhysicalDeviceSurfaceFormatsKHR(physicalDevice, handle, &count, nullptr);
    formats.resize(count);
    vkGetPhysicalDeviceSurfaceFormatsKHR(physicalDevice, handle, &count, formats.data());

    vkGetPhysicalDeviceSurfacePresentModesKHR(physicalDevice, handle, &count, nullptr);
    presentModes.resize(count);
    vkGetPhysicalDeviceSurfacePresentModesKHR(physicalDevice, handle, &count, presentModes.data());

    vkGetPhysicalDeviceSurfaceCapabilitiesKHR(physicalDevice, handle, &capabilities);

    swapchain = std::make_unique<Swapchain>(this);
    swapchain->create();
}

void Surface::destroy() {
    VULKAN_DESTROY_HANDLE(vkDestroySurfaceKHR(Instance::get()->getHandle(), handle, nullptr))
}

VkExtent2D Surface::getCurrentExtent() const {
    VkSurfaceCapabilitiesKHR capabilities;
    vkGetPhysicalDeviceSurfaceCapabilitiesKHR(physicalDevice, handle, &capabilities);
    return capabilities.currentExtent;
}
