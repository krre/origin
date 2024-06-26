#include "DeviceMemory.h"

namespace Vulkan {

DeviceMemory::DeviceMemory(Device* device) : Devicer(device) {
    m_allocateInfo.sType = VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO;
}

DeviceMemory::~DeviceMemory() {
    vkFreeMemory(m_device->handle(), m_handle, nullptr);
}

void DeviceMemory::allocate(VkDeviceSize size) {
    m_allocateInfo.allocationSize = size;
    VULKAN_CHECK_RESULT(vkAllocateMemory(m_device->handle(), &m_allocateInfo, nullptr, &m_handle), "Failed to allocate memory");
}

void DeviceMemory::setMemoryTypeIndex(uint32_t index) {
    m_allocateInfo.memoryTypeIndex = index;
}

void DeviceMemory::map(void** data, VkDeviceSize size, VkDeviceSize offset) {
    VULKAN_CHECK_RESULT(vkMapMemory(m_device->handle(), m_handle, offset, size, 0, data), "Failed to map device memory");
}

void DeviceMemory::unmap() {
    vkUnmapMemory(m_device->handle(), m_handle);
}

}
