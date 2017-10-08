#define VK_USE_PLATFORM_XCB_KHR
#include "SurfaceXcb.h"
#include "../Instance.h"

using namespace Vulkan;

SurfaceXcb::SurfaceXcb(VkPhysicalDevice physicalDevice, xcb_connection_t* connection, xcb_window_t window) :
    Surface(physicalDevice),
    connection(connection),
    window(window) {
}

void Vulkan::SurfaceXcb::platformCreateHandle() {
    VkXcbSurfaceCreateInfoKHR createInfo = {};
    createInfo.sType = VK_STRUCTURE_TYPE_XCB_SURFACE_CREATE_INFO_KHR;
    createInfo.connection = connection;
    createInfo.window = window;
    VULKAN_CHECK_RESULT(vkCreateXcbSurfaceKHR(Instance::get()->getHandle(), &createInfo, nullptr, &handle), "Failed to create Xcb surface");
}
