#include "Device.h"
#include "PhysicalDevice.h"
#include <iostream>

namespace Vulkan {

Device::Device(PhysicalDevice* physicalDevice) : m_physicalDevice(physicalDevice) {
    uint32_t count;
    vkEnumerateDeviceExtensionProperties(physicalDevice->handle(), nullptr, &count, nullptr);
    extensions.resize(count);
    vkEnumerateDeviceExtensionProperties(physicalDevice->handle(), nullptr, &count, extensions.data());

    // While only one extension is enabled
    enabledExtensions.push_back("VK_KHR_swapchain");

    createInfo.sType = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO;
    createInfo.enabledExtensionCount = enabledExtensions.size();
    createInfo.ppEnabledExtensionNames = enabledExtensions.data();
}

Device::~Device() {
    destroy();
}

void Device::waitIdle() {
    if (m_handle != VK_NULL_HANDLE) {
        vkDeviceWaitIdle(m_handle);
    }
}

void Device::waitForFences(std::vector<VkFence> fences) {
    VULKAN_CHECK_RESULT(vkWaitForFences(m_handle, fences.size(), fences.data(), VK_TRUE, UINT64_MAX), "Failed wait for fences");
}

void Device::resetFences(std::vector<VkFence> fences) {
    VULKAN_CHECK_RESULT(vkResetFences(m_handle, fences.size(), fences.data()), "Failed to reset fences")
}

void Device::create() {
    createInfo.queueCreateInfoCount = queueCreateInfos.size();
    createInfo.pQueueCreateInfos = queueCreateInfos.data();
    VULKAN_CHECK_RESULT(vkCreateDevice(m_physicalDevice->handle(), &createInfo, nullptr, &m_handle), "Failed to create device");
}

void Device::destroy() {
    VULKAN_DESTROY_HANDLE(vkDestroyDevice(m_handle, nullptr))
}

void Device::dumpExtensions() {
    for (const auto& extension : extensions) {
        std::cout << extension.extensionName << std::endl;
    }
}

void Device::addQueueCreateInfo(uint32_t queueFamilyIndex, std::vector<float> queuePriorities) {
    int offset = this->queuePriorities.size();

    // Append new priorities with queueFamilyIndex to common storage for all queueCreateInfos
    for (const auto& queuePriority : queuePriorities) {
        this->queuePriorities.push_back(queuePriority);
    }

    VkDeviceQueueCreateInfo queueCreateInfo = {};
    queueCreateInfo.sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO;
    queueCreateInfo.queueFamilyIndex = queueFamilyIndex;
    queueCreateInfo.queueCount = queuePriorities.size();
    queueCreateInfo.pQueuePriorities = &this->queuePriorities[offset];

    queueCreateInfos.push_back(queueCreateInfo);
}

}
