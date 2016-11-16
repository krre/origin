#include "VulkanManager.h"

using namespace Vulkan;

std::map<VkResult, std::string> VulkanManager::resultDescription;

VulkanManager::VulkanManager() {
    resultDescription[VK_SUCCESS] = "Success";
    resultDescription[VK_NOT_READY] = "Not ready";
    resultDescription[VK_TIMEOUT] = "Timeout";
    resultDescription[VK_EVENT_SET] = "Event set";
    resultDescription[VK_EVENT_RESET] = "Event reset";
    resultDescription[VK_INCOMPLETE] = "Incoplete";
    resultDescription[VK_ERROR_OUT_OF_HOST_MEMORY] = "Out of host memory";
    resultDescription[VK_ERROR_OUT_OF_DEVICE_MEMORY] = "Out of device memory";
    resultDescription[VK_ERROR_INITIALIZATION_FAILED] = "Initialization failed";
    resultDescription[VK_ERROR_DEVICE_LOST] = "Device lost";
    resultDescription[VK_ERROR_MEMORY_MAP_FAILED] = "Memory map failed";
    resultDescription[VK_ERROR_LAYER_NOT_PRESENT] = "Layer not present";
    resultDescription[VK_ERROR_EXTENSION_NOT_PRESENT] = "Extension not present";
    resultDescription[VK_ERROR_FEATURE_NOT_PRESENT] = "Feature not present";
    resultDescription[VK_ERROR_INCOMPATIBLE_DRIVER] = "Incompatible driver";
    resultDescription[VK_ERROR_TOO_MANY_OBJECTS] = "Too many objects";
    resultDescription[VK_ERROR_FORMAT_NOT_SUPPORTED] = "Format not supported";
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
