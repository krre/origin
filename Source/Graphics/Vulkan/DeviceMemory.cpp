#include "DeviceMemory.h"

using namespace Vulkan;

DeviceMemory::DeviceMemory(const Device* device) : device(device) {

}

DeviceMemory::~DeviceMemory() {
    vkFreeMemory(device->getHandle(), handle, nullptr);
}

VkResult DeviceMemory::create() {
    return checkError(vkAllocateMemory(device->getHandle(), &allocateInfo, nullptr, &handle), "Failed to allocate memory");
}
