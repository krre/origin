#include "CommandPool.h"

using namespace Vulkan;

CommandPool::CommandPool(const Device* device) : device(device) {
    VkCommandPoolCreateInfo createInfo = {};
    createInfo.sType = VK_STRUCTURE_TYPE_COMMAND_POOL_CREATE_INFO;
    createInfo.queueFamilyIndex = 0; // TODO: Set real family index;
    createInfo.flags = 0; // Optional

    result = vkCreateCommandPool(device->getHandle(), &createInfo, nullptr, &handle);
}

CommandPool::~CommandPool() {
    if (handle != VK_NULL_HANDLE) {
        vkDestroyCommandPool(device->getHandle(), handle, nullptr);
    }
}

bool CommandPool::reset() {
    result = vkResetCommandPool(device->getHandle(), handle, VK_COMMAND_POOL_RESET_RELEASE_RESOURCES_BIT);
    return result == VK_SUCCESS;
}
