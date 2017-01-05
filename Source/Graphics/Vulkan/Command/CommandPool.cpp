#include "CommandPool.h"

using namespace Vulkan;

CommandPool::CommandPool(const Device* device, uint32_t familyIndex) : device(device) {
    createInfo.sType = VK_STRUCTURE_TYPE_COMMAND_POOL_CREATE_INFO;
    createInfo.queueFamilyIndex = familyIndex;
}

CommandPool::~CommandPool() {
    vkDestroyCommandPool(device->getHandle(), handle, nullptr);
}

VkResult CommandPool::create() {
    return checkError(vkCreateCommandPool(device->getHandle(), &createInfo, nullptr, &handle), "Failed to create command pool");
}

VkResult CommandPool::reset() {
    return checkError(vkResetCommandPool(device->getHandle(), handle, VK_COMMAND_POOL_RESET_RELEASE_RESOURCES_BIT), "Failed to reset command pool");
}
