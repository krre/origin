#include "CommandPool.h"

namespace Vulkan {

CommandPool::CommandPool(Device* device, uint32_t queueFamilyIndex) : Devicer(device) {
    createInfo.sType = VK_STRUCTURE_TYPE_COMMAND_POOL_CREATE_INFO;
    createInfo.flags = VK_COMMAND_POOL_CREATE_RESET_COMMAND_BUFFER_BIT;
    createInfo.queueFamilyIndex = queueFamilyIndex;
}

CommandPool::~CommandPool() {
    destroy();
}

void CommandPool::create() {
    VULKAN_CHECK_RESULT(vkCreateCommandPool(device->getHandle(), &createInfo, nullptr, &handle), "Failed to create command pool")
}

void CommandPool::destroy() {
    VULKAN_DESTROY_HANDLE(vkDestroyCommandPool(device->getHandle(), handle, nullptr))
}

void CommandPool::reset() {
    VULKAN_CHECK_RESULT(vkResetCommandPool(device->getHandle(), handle, VK_COMMAND_POOL_RESET_RELEASE_RESOURCES_BIT), "Failed to reset command pool");
}

} // Vulkan
