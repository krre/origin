#include "Device.h"
#include <assert.h>

using namespace Vulkan;

Device::Device(const PhysicalDevices* physicalDevices) : physicalDevices(physicalDevices) {

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
