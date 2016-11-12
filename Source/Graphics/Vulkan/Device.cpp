#include "Device.h"

using namespace Vulkan;

Device::Device() {

}

Device::~Device() {
    if (device) {
        vkDestroyDevice(device, NULL);
    }
}

bool Device::create() {

    return false;
}
