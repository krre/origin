#include "VulkanManager.h"

using namespace Vulkan;

VulkanManager::VulkanManager() {

}

bool VulkanManager::init() {
    // Vulkan instance
    instance.reset(new Instance);
    if (!instance->isValid()) {
        error = std::string(initError) + instance->getError();
        return false;
    }

    // Vulkan device
    physicalDevices.reset(new PhysicalDevices(instance.get()));
    device.reset(new Device(physicalDevices.get()));
    if (!device->isValid()) {
        error = std::string(initError) + device->getError();
        return false;
    }

    return true;
}
