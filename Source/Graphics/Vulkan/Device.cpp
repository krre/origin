#include "Device.h"

using namespace Vulkan;

Device::Device() {

}

Device::~Device() {
    if (handle) {
        vkDestroyDevice(handle, NULL);
    }
}

bool Device::create() {

    return false;
}
