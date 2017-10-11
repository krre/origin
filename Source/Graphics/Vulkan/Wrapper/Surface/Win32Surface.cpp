#define VK_USE_PLATFORM_WIN32_KHR
#include "Win32Surface.h"
#include "../Instance.h"

using namespace Vulkan;

Win32Surface::Win32Surface(VkInstance instance, VkPhysicalDevice physicalDevice, HINSTANCE hinstance, HWND hwnd) :
    Surface(instance, physicalDevice),
    hinstance(hinstance),
    hwnd(hwnd) {
}

void Vulkan::Win32Surface::platformCreateHandle() {
    VkWin32SurfaceCreateInfoKHR createInfo = {};
    createInfo.sType = VK_STRUCTURE_TYPE_WIN32_SURFACE_CREATE_INFO_KHR;
    createInfo.hinstance = hinstance;
    createInfo.hwnd = hwnd;
    VULKAN_CHECK_RESULT(vkCreateWin32SurfaceKHR(Instance::get()->getHandle(), &createInfo, nullptr, &handle), "Failed to create win32 surface");
}
