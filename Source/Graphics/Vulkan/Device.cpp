#include "Device.h"

using namespace Vulkan;

Device::Device(VkPhysicalDevice physicalDevice, uint32_t familyIndex) : physicalDevice(physicalDevice) {
    float queuePriority = 1.0f;
    VkDeviceQueueCreateInfo queueCreateInfo = {};
    queueCreateInfo.sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO;
    queueCreateInfo.queueCount = 1;
    queueCreateInfo.pQueuePriorities = &queuePriority;
    queueCreateInfo.queueFamilyIndex = familyIndex;

    uint32_t extensionCount;
    vkEnumerateDeviceExtensionProperties(physicalDevice, nullptr, &extensionCount, nullptr);
    std::vector<VkExtensionProperties> availableExtensions(extensionCount);
    vkEnumerateDeviceExtensionProperties(physicalDevice, nullptr, &extensionCount, availableExtensions.data());
    std::vector<const char*> extNames;
    print("Physical device extensions:")
    for (const auto& extension : availableExtensions) {
        print(extension.extensionName);
        extNames.push_back(extension.extensionName);
    }
    print("")

    VkDeviceCreateInfo createInfo = {};
    createInfo.sType = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO;
    createInfo.queueCreateInfoCount = 1;
    createInfo.pQueueCreateInfos = &queueCreateInfo;
    createInfo.enabledLayerCount = 0;
    createInfo.enabledExtensionCount = extensionCount;
    createInfo.ppEnabledExtensionNames = extNames.data();

    result = vkCreateDevice(physicalDevice, &createInfo, nullptr, &handle);
}

Device::~Device() {
    if (handle != VK_NULL_HANDLE) {
        vkDestroyDevice(handle, nullptr);
    }
}

void Device::waitIdle() {
    if (handle != VK_NULL_HANDLE) {
        vkDeviceWaitIdle(handle);
    }
}
