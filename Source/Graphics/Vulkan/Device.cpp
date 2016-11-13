#include "Device.h"

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
