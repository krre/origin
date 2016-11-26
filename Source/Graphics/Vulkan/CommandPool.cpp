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
