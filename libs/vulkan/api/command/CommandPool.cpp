#include "CommandPool.h"

namespace Vulkan {

CommandPool::CommandPool(Device* device, uint32_t queueFamilyIndex) : Devicer(device) {
    m_createInfo.sType = VK_STRUCTURE_TYPE_COMMAND_POOL_CREATE_INFO;
    m_createInfo.flags = VK_COMMAND_POOL_CREATE_RESET_COMMAND_BUFFER_BIT;
    m_createInfo.queueFamilyIndex = queueFamilyIndex;
}

CommandPool::~CommandPool() {
    destroy();
}

void CommandPool::create() {
    VULKAN_CHECK_RESULT(vkCreateCommandPool(m_device->handle(), &m_createInfo, nullptr, &m_handle), "Failed to create command pool")
}

void CommandPool::destroy() {
    VULKAN_DESTROY_HANDLE(vkDestroyCommandPool(m_device->handle(), m_handle, nullptr))
}

void CommandPool::reset() {
    VULKAN_CHECK_RESULT(vkResetCommandPool(m_device->handle(), m_handle, VK_COMMAND_POOL_RESET_RELEASE_RESOURCES_BIT), "Failed to reset command pool");
}

}
