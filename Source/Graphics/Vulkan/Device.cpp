#include "Device.h"

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

    result = vkCreateDevice(physicalDevices->getPrimary(), &createInfo, nullptr, &handle);
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
