#include "Fence.h"

using namespace Vulkan;

Fence::Fence(Device* device) : Devicer(device) {
    createInfo.sType = VK_STRUCTURE_TYPE_FENCE_CREATE_INFO;
}

Fence::~Fence() {
    destroy();
}

void Fence::create() {
    VULKAN_CHECK_RESULT(vkCreateFence(device->getHandle(), &createInfo, nullptr, &handle), "Failed to create fence");
}

void Fence::destroy() {
    VULKAN_DESTROY_HANDLE(vkDestroyFence(device->getHandle(), handle, nullptr))
}

VkResult Fence::wait() {
    return vkWaitForFences(device->getHandle(), 1, &handle, VK_TRUE, UINT64_MAX);
}

VkResult Fence::reset() {
    return vkResetFences(device->getHandle(), 1, &handle);
}

void Fence::setSignaledBit() {
    createInfo.flags = VK_FENCE_CREATE_SIGNALED_BIT;
}
