#include "Fence.h"

using namespace Vulkan;

Fence::Fence(const Device* device) : device(device) {
    VkFenceCreateInfo createInfo = {};
    createInfo.sType = VK_STRUCTURE_TYPE_FENCE_CREATE_INFO;
    createInfo.pNext = nullptr;
    createInfo.flags = 0;

    result = vkCreateFence(device->getHandle(), &createInfo, nullptr, &handle);
}

Fence::~Fence() {
    if (handle != VK_NULL_HANDLE) {
        vkDestroyFence(device->getHandle(), handle, nullptr);
    }
}

VkResult Fence::wait(uint32_t count) {
    vkWaitForFences(device->getHandle(), count, &handle, VK_TRUE, 100000000);
}
