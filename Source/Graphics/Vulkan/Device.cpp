#include "Device.h"

using namespace Vulkan;

Device::Device(VkPhysicalDevice physicalDevice, uint32_t familyIndex) : physicalDevice(physicalDevice) {
    uint32_t count;
    vkEnumerateDeviceExtensionProperties(physicalDevice, nullptr, &count, nullptr);
    extensions.resize(count);
    vkEnumerateDeviceExtensionProperties(physicalDevice, nullptr, &count, extensions.data());

    for (const auto& extension : extensions) {
        enabledExtensions.push_back(extension.extensionName);
    }

    float queuePriority = 1.0f;
    VkDeviceQueueCreateInfo queueCreateInfo = {};
    queueCreateInfo.sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO;
    queueCreateInfo.queueCount = 1;
    queueCreateInfo.pQueuePriorities = &queuePriority;
    queueCreateInfo.queueFamilyIndex = familyIndex;

    createInfo.sType = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO;
    createInfo.pNext = nullptr;
    createInfo.queueCreateInfoCount = 1;
    createInfo.pQueueCreateInfos = &queueCreateInfo;
    createInfo.enabledLayerCount = 0;
    createInfo.enabledExtensionCount = enabledExtensions.size();
    createInfo.ppEnabledExtensionNames = enabledExtensions.data();
    createInfo.pEnabledFeatures = nullptr;
}

Device::~Device() {
    vkDestroyDevice(handle, nullptr);
}

void Device::waitIdle() {
    if (handle != VK_NULL_HANDLE) {
        vkDeviceWaitIdle(handle);
    }
}

void Device::create() {
    checkError(vkCreateDevice(physicalDevice, &createInfo, nullptr, &handle));
}

void Device::dumpExtensions() {
    for (const auto& extension : extensions) {
        print(extension.extensionName);
    }
}
