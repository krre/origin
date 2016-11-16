#include "Device.h"
#include <assert.h>

using namespace Vulkan;

Device::Device(const PhysicalDevices* physicalDevices) : physicalDevices(physicalDevices) {
    float queuePriority = 1.0f;
    VkDeviceQueueCreateInfo queueCreateInfo;
    queueCreateInfo.sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO;
    queueCreateInfo.queueCount = 1;
    queueCreateInfo.pQueuePriorities = &queuePriority;

    uint32_t familyCount;
    vkGetPhysicalDeviceQueueFamilyProperties(physicalDevices->getPrimary(), &familyCount, nullptr);
    std::vector<VkQueueFamilyProperties> familyProperties(familyCount);
    vkGetPhysicalDeviceQueueFamilyProperties(physicalDevices->getPrimary(), &familyCount, familyProperties.data());

    bool found = false;
    for (int i = 0; i < familyCount; i++) {
        if (familyProperties[i].queueFlags & VK_QUEUE_GRAPHICS_BIT) {
            queueCreateInfo.queueFamilyIndex = i;
            found = true;
            break;
        }
    }

    VkDeviceCreateInfo createInfo;
    createInfo.sType = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO;
    createInfo.queueCreateInfoCount = 1;
    createInfo.pQueueCreateInfos = &queueCreateInfo;
    createInfo.enabledLayerCount = 0;
    createInfo.enabledExtensionCount = 0;

    VkResult result = vkCreateDevice(physicalDevices->getPrimary(), &createInfo, nullptr, &handle);

    if (result != VK_SUCCESS) {
        switch (result) {
        case VK_ERROR_OUT_OF_HOST_MEMORY:
            error = "Out of host memory";
            break;
        case VK_ERROR_OUT_OF_DEVICE_MEMORY:
            error = "Out of device memory";
            break;
        case VK_ERROR_INITIALIZATION_FAILED:
            error = "Initialization failed";
            break;
        case VK_ERROR_EXTENSION_NOT_PRESENT:
            error = "Extension not present";
            break;
        case VK_ERROR_FEATURE_NOT_PRESENT:
            error = "Feature not present";
            break;
        case VK_ERROR_TOO_MANY_OBJECTS:
            error = "Too many objects";
            break;
        case VK_ERROR_DEVICE_LOST:
            error = "Device lost";
        }
    }
}

Device::~Device() {
    if (handle) {
        vkDestroyDevice(handle, nullptr);
    }
}

void Device::waitIdle() {
    if (handle) {
        vkDeviceWaitIdle(handle);
    }
}
