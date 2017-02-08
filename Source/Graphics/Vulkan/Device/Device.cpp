#include "Device.h"

using namespace Vulkan;

Device::Device(PhysicalDevice* physicalDevice, uint32_t familyIndex) : physicalDevice(physicalDevice) {
    uint32_t count;
    vkEnumerateDeviceExtensionProperties(physicalDevice->getHandle(), nullptr, &count, nullptr);
    extensions.resize(count);
    vkEnumerateDeviceExtensionProperties(physicalDevice->getHandle(), nullptr, &count, extensions.data());

    for (const auto& extension : extensions) {
        enabledExtensions.push_back(extension.extensionName);
    }

    queueCreateInfo.sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO;
    queueCreateInfo.queueCount = 1;
    queueCreateInfo.pQueuePriorities = &queuePriority;
    queueCreateInfo.queueFamilyIndex = familyIndex;

    createInfo.sType = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO;
    createInfo.queueCreateInfoCount = 1;
    createInfo.pQueueCreateInfos = &queueCreateInfo;
    createInfo.enabledExtensionCount = enabledExtensions.size();
    createInfo.ppEnabledExtensionNames = enabledExtensions.data();
}

Device::~Device() {
    destroy();
}

void Device::waitIdle() {
    if (handle != VK_NULL_HANDLE) {
        vkDeviceWaitIdle(handle);
    }
}

void Device::waitForFences(uint32_t count, const VkFence* fences) {
    vkWaitForFences(handle, count, fences, VK_TRUE, DEFAULT_FENCE_TIMEOUT);
}

void Device::waitForFences(std::vector<VkFence> fences) {
    vkWaitForFences(handle, fences.size(), fences.data(), VK_TRUE, DEFAULT_FENCE_TIMEOUT);
}

VkResult Device::create() {
    CHECK_RESULT(vkCreateDevice(physicalDevice->getHandle(), &createInfo, nullptr, &handle), "Failed to create device");
    return result;
}

void Device::destroy() {
    VULKAN_DESTROY_HANDLE(vkDestroyDevice(handle, nullptr))
}

void Device::dumpExtensions() {
    for (const auto& extension : extensions) {
        PRINT(extension.extensionName);
    }
}
