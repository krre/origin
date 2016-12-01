#include "CommandPool.h"

using namespace Vulkan;

CommandPool::CommandPool(const Device* device) : device(device) {
    createInfo.sType = VK_STRUCTURE_TYPE_COMMAND_POOL_CREATE_INFO;
    createInfo.pNext = nullptr;
    createInfo.queueFamilyIndex = 0; // TODO: Set real family index;
    createInfo.flags = 0;
}

CommandPool::~CommandPool() {
    vkDestroyCommandPool(device->getHandle(), handle, nullptr);
}

void CommandPool::create() {
    checkError(vkCreateCommandPool(device->getHandle(), &createInfo, nullptr, &handle));
}

bool CommandPool::reset() {
    result = vkResetCommandPool(device->getHandle(), handle, VK_COMMAND_POOL_RESET_RELEASE_RESOURCES_BIT);
    return result == VK_SUCCESS;
}
