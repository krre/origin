#include "DeviceMemory.h"

using namespace Vulkan;

DeviceMemory::DeviceMemory(const Device* device) : device(device) {
    allocateInfo.sType = VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO;
}

DeviceMemory::~DeviceMemory() {
    vkFreeMemory(device->getHandle(), handle, nullptr);
}

VkResult DeviceMemory::allocate() {
    return checkError(vkAllocateMemory(device->getHandle(), &allocateInfo, nullptr, &handle), "Failed to allocate memory");
}

void DeviceMemory::setAllocationSize(VkDeviceSize allocationSize) {
    allocateInfo.allocationSize = allocationSize;
}

void DeviceMemory::setMemoryTypeIndex(uint32_t index) {
    allocateInfo.memoryTypeIndex = index;
}
