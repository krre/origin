#if defined(_WIN32)
    #define VK_USE_PLATFORM_WIN32_KHR
    #include <windows.h>
#else
    #define VK_USE_PLATFORM_XCB_KHR
    #include <X11/Xlib-xcb.h>
#endif

#include "Surface.h"
#include "../Instance.h"
#include "../device/PhysicalDevice.h"

namespace Vulkan {

Surface::Surface(Instance* instance, PhysicalDevice* physicalDevice, void* platformHandle, void* platformWindow) :
    instance(instance),
    physicalDevice(physicalDevice),
    platformHandle(platformHandle),
    platformWindow(platformWindow) {
}

Surface::~Surface() {
    destroy();
}

void Surface::create() {
#if defined(VK_USE_PLATFORM_XCB_KHR)
    VkXcbSurfaceCreateInfoKHR createInfo = {};
    createInfo.sType = VK_STRUCTURE_TYPE_XCB_SURFACE_CREATE_INFO_KHR;
    createInfo.connection = (xcb_connection_t*)platformHandle;
    createInfo.window = *(xcb_window_t*)(platformWindow);
    VULKAN_CHECK_RESULT(vkCreateXcbSurfaceKHR(instance->handle(), &createInfo, nullptr, &m_handle), "Failed to create Xcb surface");
#elif defined(VK_USE_PLATFORM_WIN32_KHR)
    VkWin32SurfaceCreateInfoKHR createInfo = {};
    createInfo.sType = VK_STRUCTURE_TYPE_WIN32_SURFACE_CREATE_INFO_KHR;
    createInfo.hinstance = (HINSTANCE)platformHandle;
    createInfo.hwnd = (HWND)platformWindow;
    VULKAN_CHECK_RESULT(vkCreateWin32SurfaceKHR(instance->getHandle(), &createInfo, nullptr, &handle), "Failed to create win32 surface");
#endif

    uint32_t count;
    vkGetPhysicalDeviceSurfaceFormatsKHR(physicalDevice->handle(), m_handle, &count, nullptr);
    m_formats.resize(count);
    vkGetPhysicalDeviceSurfaceFormatsKHR(physicalDevice->handle(), m_handle, &count, m_formats.data());

    vkGetPhysicalDeviceSurfacePresentModesKHR(physicalDevice->handle(), m_handle, &count, nullptr);
    m_presentModes.resize(count);
    vkGetPhysicalDeviceSurfacePresentModesKHR(physicalDevice->handle(), m_handle, &count, m_presentModes.data());

    vkGetPhysicalDeviceSurfaceCapabilitiesKHR(physicalDevice->handle(), m_handle, &m_capabilities);
}

void Surface::destroy() {
    VULKAN_DESTROY_HANDLE(vkDestroySurfaceKHR(instance->handle(), m_handle, nullptr))
}

VkExtent2D Surface::currentExtent() const {
    VkSurfaceCapabilitiesKHR capabilities;
    vkGetPhysicalDeviceSurfaceCapabilitiesKHR(physicalDevice->handle(), m_handle, &capabilities);
    return capabilities.currentExtent;
}

}
