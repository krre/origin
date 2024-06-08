#include "Device.h"
#include "PhysicalDevice.h"
#include <iostream>

namespace Vulkan {

Device::Device(PhysicalDevice* physicalDevice) : m_physicalDevice(physicalDevice) {
    uint32_t count;
    vkEnumerateDeviceExtensionProperties(physicalDevice->handle(), nullptr, &count, nullptr);
    m_extensions.resize(count);
    vkEnumerateDeviceExtensionProperties(physicalDevice->handle(), nullptr, &count, m_extensions.data());

    // While only one extension is enabled
    m_enabledExtensions.push_back("VK_KHR_swapchain");

    m_createInfo.sType = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO;
    m_createInfo.enabledExtensionCount = m_enabledExtensions.size();
    m_createInfo.ppEnabledExtensionNames = m_enabledExtensions.data();
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
    m_createInfo.queueCreateInfoCount = m_queueCreateInfos.size();
    m_createInfo.pQueueCreateInfos = m_queueCreateInfos.data();
    VULKAN_CHECK_RESULT(vkCreateDevice(m_physicalDevice->handle(), &m_createInfo, nullptr, &m_handle), "Failed to create device");
}

void Device::destroy() {
    VULKAN_DESTROY_HANDLE(vkDestroyDevice(m_handle, nullptr))
}

void Device::dumpExtensions() {
    for (const auto& extension : m_extensions) {
        std::cout << extension.extensionName << std::endl;
    }
}

void Device::addQueueCreateInfo(uint32_t queueFamilyIndex, std::vector<float> queuePriorities) {
    int offset = m_queuePriorities.size();

    // Append new priorities with queueFamilyIndex to common storage for all queueCreateInfos
    for (const auto& queuePriority : queuePriorities) {
        m_queuePriorities.push_back(queuePriority);
    }

    VkDeviceQueueCreateInfo queueCreateInfo = {};
    queueCreateInfo.sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO;
    queueCreateInfo.queueFamilyIndex = queueFamilyIndex;
    queueCreateInfo.queueCount = queuePriorities.size();
    queueCreateInfo.pQueuePriorities = &m_queuePriorities[offset];

    m_queueCreateInfos.push_back(queueCreateInfo);
}

}
