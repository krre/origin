#include "Fence.h"

using namespace Vulkan;

Fence::Fence(const Device* device) : device(device) {
    createInfo.sType = VK_STRUCTURE_TYPE_FENCE_CREATE_INFO;
}

Fence::~Fence() {
    vkDestroyFence(device->getHandle(), handle, nullptr);
}

VkResult Fence::create() {
    return checkError(vkCreateFence(device->getHandle(), &createInfo, nullptr, &handle), "Failed to create fence");
}

VkResult Fence::wait(uint32_t count) {
    return vkWaitForFences(device->getHandle(), count, &handle, VK_TRUE, 100000000);
}

VkResult Fence::reset(uint32_t count) {
    return vkResetFences(device->getHandle(), count, &handle);
}
