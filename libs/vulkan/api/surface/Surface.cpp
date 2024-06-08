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
    m_instance(instance),
    m_physicalDevice(physicalDevice),
    m_platformHandle(platformHandle),
    m_platformWindow(platformWindow) {
}

Surface::~Surface() {
    destroy();
}

void Surface::create() {
#if defined(VK_USE_PLATFORM_XCB_KHR)
    VkXcbSurfaceCreateInfoKHR createInfo = {};
    createInfo.sType = VK_STRUCTURE_TYPE_XCB_SURFACE_CREATE_INFO_KHR;
    createInfo.connection = (xcb_connection_t*)m_platformHandle;
    createInfo.window = *(xcb_window_t*)(m_platformWindow);
    VULKAN_CHECK_RESULT(vkCreateXcbSurfaceKHR(m_instance->handle(), &createInfo, nullptr, &m_handle), "Failed to create Xcb surface");
#elif defined(VK_USE_PLATFORM_WIN32_KHR)
    VkWin32SurfaceCreateInfoKHR createInfo = {};
    createInfo.sType = VK_STRUCTURE_TYPE_WIN32_SURFACE_CREATE_INFO_KHR;
    createInfo.hinstance = (HINSTANCE)platformHandle;
    createInfo.hwnd = (HWND)platformWindow;
    VULKAN_CHECK_RESULT(vkCreateWin32SurfaceKHR(instance->getHandle(), &createInfo, nullptr, &handle), "Failed to create win32 surface");
#endif

    uint32_t count;
    vkGetPhysicalDeviceSurfaceFormatsKHR(m_physicalDevice->handle(), m_handle, &count, nullptr);
    m_formats.resize(count);
    vkGetPhysicalDeviceSurfaceFormatsKHR(m_physicalDevice->handle(), m_handle, &count, m_formats.data());

    vkGetPhysicalDeviceSurfacePresentModesKHR(m_physicalDevice->handle(), m_handle, &count, nullptr);
    m_presentModes.resize(count);
    vkGetPhysicalDeviceSurfacePresentModesKHR(m_physicalDevice->handle(), m_handle, &count, m_presentModes.data());

    vkGetPhysicalDeviceSurfaceCapabilitiesKHR(m_physicalDevice->handle(), m_handle, &m_capabilities);
}

void Surface::destroy() {
    VULKAN_DESTROY_HANDLE(vkDestroySurfaceKHR(m_instance->handle(), m_handle, nullptr))
}

VkExtent2D Surface::currentExtent() const {
    VkSurfaceCapabilitiesKHR capabilities;
    vkGetPhysicalDeviceSurfaceCapabilitiesKHR(m_physicalDevice->handle(), m_handle, &capabilities);
    return capabilities.currentExtent;
}

}
