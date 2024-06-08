#include "Buffer.h"

namespace Vulkan {

Buffer::Buffer(Device* device, VkBufferUsageFlagBits usage, VkDeviceSize size) :
        Devicer(device) {
    m_createInfo.sType = VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO;
    m_createInfo.size = size;
    m_createInfo.usage = usage;
    m_createInfo.sharingMode = VK_SHARING_MODE_EXCLUSIVE;
}

Buffer::~Buffer() {
    destroy();
}

void Buffer::create() {
    VULKAN_CHECK_RESULT(vkCreateBuffer(m_device->handle(), &m_createInfo, nullptr, &m_handle), "Failed to create buffer");
}

void Buffer::destroy() {
    VULKAN_DESTROY_HANDLE(vkDestroyBuffer(m_device->handle(), m_handle, nullptr))
}

}
