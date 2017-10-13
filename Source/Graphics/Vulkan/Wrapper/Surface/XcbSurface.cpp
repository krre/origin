#define VK_USE_PLATFORM_XCB_KHR
#include "XcbSurface.h"
#include "../Instance.h"

using namespace Vulkan;

XcbSurface::XcbSurface(Instance* instance, PhysicalDevice* physicalDevice, xcb_connection_t* connection, xcb_window_t window) :
    Surface(instance, physicalDevice),
    connection(connection),
    window(window) {
}

void Vulkan::XcbSurface::platformCreateHandle() {
    VkXcbSurfaceCreateInfoKHR createInfo = {};
    createInfo.sType = VK_STRUCTURE_TYPE_XCB_SURFACE_CREATE_INFO_KHR;
    createInfo.connection = connection;
    createInfo.window = window;
    VULKAN_CHECK_RESULT(vkCreateXcbSurfaceKHR(instance->getHandle(), &createInfo, nullptr, &handle), "Failed to create Xcb surface");
}
