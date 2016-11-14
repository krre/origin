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
