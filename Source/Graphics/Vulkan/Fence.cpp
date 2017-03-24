#include "Fence.h"

using namespace Vulkan;

Fence::Fence(const Device* device) : Devicer(device) {
    createInfo.sType = VK_STRUCTURE_TYPE_FENCE_CREATE_INFO;
}

Fence::~Fence() {
    destroy();
}

void Fence::create() {
    CHECK_RESULT(vkCreateFence(device->getHandle(), &createInfo, nullptr, &handle), "Failed to create fence");
}

void Fence::destroy() {
    VULKAN_DESTROY_HANDLE(vkDestroyFence(device->getHandle(), handle, nullptr))
}

VkResult Fence::wait(uint32_t count) {
    return vkWaitForFences(device->getHandle(), count, &handle, VK_TRUE, 100000000);
}

VkResult Fence::reset(uint32_t count) {
    return vkResetFences(device->getHandle(), count, &handle);
}
