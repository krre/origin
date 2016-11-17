#include "VulkanManager.h"

using namespace Vulkan;

VulkanManager::VulkanManager() {

}

bool VulkanManager::init() {
    // Vulkan instance
    instance.reset(new Instance);
    if (!instance->isValid()) {
        resultDescription = std::string(initError) + instance->getResultDescription();
        return false;
    }

    // Vulkan device
    physicalDevices.reset(new PhysicalDevices(instance.get()));
    device.reset(new Device(physicalDevices.get()));
    if (!device->isValid()) {
        resultDescription = std::string(initError) + device->getResultDescription();
        return false;
    }

    // Vulkan surface
    surface.reset(new Surface(instance.get()));

    return true;
}
