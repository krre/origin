#include "Device.h"
#include "Core/Common.h"

using namespace Vulkan;

Device::Device(PhysicalDevice* physicalDevice) : physicalDevice(physicalDevice) {
    uint32_t count;
    vkEnumerateDeviceExtensionProperties(physicalDevice->getHandle(), nullptr, &count, nullptr);
    extensions.resize(count);
    vkEnumerateDeviceExtensionProperties(physicalDevice->getHandle(), nullptr, &count, extensions.data());

    for (const auto& extension : extensions) {
        enabledExtensions.push_back(extension.extensionName);
    }

    createInfo.sType = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO;
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

VkResult Device::waitForFences(std::vector<VkFence> fences) {
    vkWaitForFences(handle, fences.size(), fences.data(), VK_TRUE, DEFAULT_FENCE_TIMEOUT);
}

void Device::create() {
    createInfo.queueCreateInfoCount = queueCreateInfos.size();
    createInfo.pQueueCreateInfos = queueCreateInfos.data();
    VULKAN_CHECK_RESULT(vkCreateDevice(physicalDevice->getHandle(), &createInfo, nullptr, &handle), "Failed to create device");
}

void Device::destroy() {
    VULKAN_DESTROY_HANDLE(vkDestroyDevice(handle, nullptr))
}

void Device::dumpExtensions() {
    for (const auto& extension : extensions) {
        PRINT(extension.extensionName);
    }
}

void Device::addQueueCreateInfo(uint32_t queueFamilyIndex, std::vector<float> queuePriorities) {
    int offset = this->queuePriorities.size();

    // Append new priorities with queueFamilyIndex to common storage for all queueCreateInfos
    for (auto& queuePriority : queuePriorities) {
        this->queuePriorities.push_back(queuePriority);
    }

    VkDeviceQueueCreateInfo queueCreateInfo = {};
    queueCreateInfo.sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO;
    queueCreateInfo.queueFamilyIndex = queueFamilyIndex;
    queueCreateInfo.queueCount = queuePriorities.size();
    queueCreateInfo.pQueuePriorities = &this->queuePriorities[offset];

    queueCreateInfos.push_back(queueCreateInfo);
}
