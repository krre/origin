#include "DeviceMemory.h"

using namespace Vulkan;

DeviceMemory::DeviceMemory(const Device* device) : device(device) {
    allocateInfo.sType = VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO;
}

DeviceMemory::~DeviceMemory() {
    if (handle != VK_NULL_HANDLE) {
        vkFreeMemory(device->getHandle(), handle, nullptr);
    }
}

VkResult DeviceMemory::allocate(VkDeviceSize size) {
    allocateInfo.allocationSize = size;
    return checkError(vkAllocateMemory(device->getHandle(), &allocateInfo, nullptr, &handle), "Failed to allocate memory");
}

void DeviceMemory::setMemoryTypeIndex(uint32_t index) {
    allocateInfo.memoryTypeIndex = index;
}

void DeviceMemory::map(VkDeviceSize count, VkDeviceSize offset, const char* data) {
    vkMapMemory(device->getHandle(), handle, offset, count, 0, (void**)&data);
}
