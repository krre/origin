#include "Swapchain.h"

using namespace Vulkan;

Swapchain::Swapchain(const Device* device) : device(device) {

}

Swapchain::~Swapchain() {
    if (handle) {
        vkDestroySwapchainKHR(device->getHandle(), handle, nullptr);
    }
}
