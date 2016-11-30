#include "DeviceMemory.h"

using namespace Vulkan;

DeviceMemory::DeviceMemory(const Device* device) : device(device) {

}

DeviceMemory::~DeviceMemory() {
    vkFreeMemory(device->getHandle(), handle, nullptr);
}

void DeviceMemory::create() {
    checkError(vkAllocateMemory(device->getHandle(), &allocateInfo, nullptr, &handle));
}
