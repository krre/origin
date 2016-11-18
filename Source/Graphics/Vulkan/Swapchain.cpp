#include "Swapchain.h"

using namespace Vulkan;

Swapchain::Swapchain(const Device* device, const Surface* surface) : device(device) {
    VkSwapchainCreateInfoKHR createInfo;
    createInfo.sType = VK_STRUCTURE_TYPE_SWAPCHAIN_CREATE_INFO_KHR;
    createInfo.surface = surface->getHandle();
    result = vkCreateSwapchainKHR(device->getHandle(), &createInfo, nullptr, &handle);
    print(handle);
}

Swapchain::~Swapchain() {
    if (handle) {
        vkDestroySwapchainKHR(device->getHandle(), handle, nullptr);
    }
}
