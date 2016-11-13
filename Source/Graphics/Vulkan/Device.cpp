#include "Device.h"
#include <assert.h>

using namespace Vulkan;

Device::Device(const PhysicalDevice* physicalDevice) : physicalDevice(physicalDevice) {

}

Device::~Device() {
    if (handle) {
        vkDestroyDevice(handle, nullptr);
    }
}

bool Device::create() {
    assert(!handle && "Vulkan device already is created");

    return false;
}

VkDevice Device::getHandle() const {
    assert(handle && "Vulkan device is not created");

    return handle;
}
