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

    uint32_t extensionCount;
    vkEnumerateDeviceExtensionProperties(physicalDevices->getPrimary(), nullptr, &extensionCount, nullptr);
    std::vector<VkExtensionProperties> availableExtensions(extensionCount);
    vkEnumerateDeviceExtensionProperties(physicalDevices->getPrimary(), nullptr, &extensionCount, availableExtensions.data());
    std::vector<const char*> extNames;
    for (const auto& extension : availableExtensions) {
        print(extension.extensionName);
        extNames.push_back(extension.extensionName);
    }

    VkDeviceCreateInfo createInfo;
    createInfo.sType = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO;
    createInfo.queueCreateInfoCount = 1;
    createInfo.pQueueCreateInfos = &queueCreateInfo;
    createInfo.enabledLayerCount = 0;
    createInfo.enabledExtensionCount = extensionCount;
    createInfo.ppEnabledExtensionNames = extNames.data();

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
