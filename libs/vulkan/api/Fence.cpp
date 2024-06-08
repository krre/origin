#include "Fence.h"

namespace Vulkan {

Fence::Fence(Device* device) : Devicer(device) {
    m_createInfo.sType = VK_STRUCTURE_TYPE_FENCE_CREATE_INFO;
}

Fence::~Fence() {
    destroy();
}

void Fence::create() {
    VULKAN_CHECK_RESULT(vkCreateFence(m_device->handle(), &m_createInfo, nullptr, &m_handle), "Failed to create fence");
}

void Fence::destroy() {
    VULKAN_DESTROY_HANDLE(vkDestroyFence(m_device->handle(), m_handle, nullptr))
}

VkResult Fence::wait() {
    return vkWaitForFences(m_device->handle(), 1, &m_handle, VK_TRUE, UINT64_MAX);
}

VkResult Fence::reset() {
    return vkResetFences(m_device->handle(), 1, &m_handle);
}

void Fence::setSignaledBit() {
    m_createInfo.flags = VK_FENCE_CREATE_SIGNALED_BIT;
}

}
