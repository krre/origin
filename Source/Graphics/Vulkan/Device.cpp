#include "Device.h"
#include <assert.h>

using namespace Vulkan;

Device::Device() {

}

Device::~Device() {
    if (handle) {
        vkDestroyDevice(handle, nullptr);
    }
}

bool Device::create() {

    return false;
}

VkDevice Device::getHandle() const {
    assert(handle && "Vulkan device is not created");

    return handle;
}
