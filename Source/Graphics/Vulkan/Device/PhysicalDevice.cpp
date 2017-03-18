#include "PhysicalDevice.h"

using namespace Vulkan;

PhysicalDevice::PhysicalDevice(VkPhysicalDevice physicalDevice)  {
    handle = physicalDevice;
}

VkFormat PhysicalDevice::getSupportedDepthFormat() {
    // Since all depth formats may be optional, we need to find a suitable depth format to use
    // Start with the highest precision packed format
    std::vector<VkFormat> depthFormats = {
        VK_FORMAT_D32_SFLOAT_S8_UINT,
        VK_FORMAT_D32_SFLOAT,
        VK_FORMAT_D24_UNORM_S8_UINT,
        VK_FORMAT_D16_UNORM_S8_UINT,
        VK_FORMAT_D16_UNORM
    };

    for (auto& format : depthFormats)     {
        VkFormatProperties formatProps;
        vkGetPhysicalDeviceFormatProperties(handle, format, &formatProps);
        // Format must support depth stencil attachment for optimal tiling
        if (formatProps.optimalTilingFeatures & VK_FORMAT_FEATURE_DEPTH_STENCIL_ATTACHMENT_BIT) {
            return format;
        }
    }

    return VK_FORMAT_UNDEFINED;
}

uint32_t PhysicalDevice::findQueue(VkQueueFlags flags) {
    uint32_t i = 0;
    for (auto& familyProperty : queueFamilyProperties) {
        if (familyProperty.queueCount > 0 && (familyProperty.queueFlags & flags)) {
            return i;
        }
        i++;
    }

    return -1;
}

uint32_t PhysicalDevice::findMemoryType(uint32_t typeFilter, VkMemoryPropertyFlags properties) {
    for (uint32_t i = 0; i < memoryProperties.memoryTypeCount; i++) {
        if ((typeFilter & (1 << i)) && (memoryProperties.memoryTypes[i].propertyFlags & properties) == properties) {
            return i;
        }
    }

    return -1;
}
