#include "PhysicalDevice.h"
#include "../Instance.h"
#include "../surface/Surface.h"

namespace Vulkan {

PhysicalDevice::PhysicalDevice(VkPhysicalDevice physicalDevice) : Handle(physicalDevice) {
    vkGetPhysicalDeviceProperties(m_handle, &m_properties);
    vkGetPhysicalDeviceFeatures(m_handle, &m_features);
    vkGetPhysicalDeviceMemoryProperties(m_handle, &m_memoryProperties);

    uint32_t count;
    vkGetPhysicalDeviceQueueFamilyProperties(m_handle, &count, nullptr);
    m_queueFamilyProperties.resize(count);
    vkGetPhysicalDeviceQueueFamilyProperties(m_handle, &count, m_queueFamilyProperties.data());
}

VkFormat PhysicalDevice::supportedDepthFormat() {
    // Since all depth formats may be optional, we need to find a suitable depth format to use
    // Start with the highest precision packed format
    std::vector<VkFormat> depthFormats = {
        VK_FORMAT_D32_SFLOAT_S8_UINT,
        VK_FORMAT_D32_SFLOAT,
        VK_FORMAT_D24_UNORM_S8_UINT,
        VK_FORMAT_D16_UNORM_S8_UINT,
        VK_FORMAT_D16_UNORM
    };

    for (const auto& format : depthFormats) {
        VkFormatProperties formatProps;
        vkGetPhysicalDeviceFormatProperties(m_handle, format, &formatProps);
        // Format must support depth stencil attachment for optimal tiling
        if (formatProps.optimalTilingFeatures & VK_FORMAT_FEATURE_DEPTH_STENCIL_ATTACHMENT_BIT) {
            return format;
        }
    }

    return VK_FORMAT_UNDEFINED;
}

bool PhysicalDevice::supportBlit(VkFormat format) {
    // Get format properties for the swapchain color format
    VkFormatProperties formatProps;
    bool supportsBlit = true;

    // Check blit support for source and destination

    // Check if the device supports blitting from optimal images (the swapchain images are in optimal format)
    vkGetPhysicalDeviceFormatProperties(m_handle, format, &formatProps);
    if (!(formatProps.optimalTilingFeatures & VK_FORMAT_FEATURE_BLIT_SRC_BIT)) {
//        std::cerr << "Device does not support blitting from optimal tiled images, using copy instead of blit!" << std::endl;
        supportsBlit = false;
    }

    // Check if the device supports blitting to linear images
    vkGetPhysicalDeviceFormatProperties(m_handle, VK_FORMAT_R8G8B8A8_UNORM, &formatProps);
    if (!(formatProps.linearTilingFeatures & VK_FORMAT_FEATURE_BLIT_DST_BIT)) {
//        std::cerr << "Device does not support blitting to linear tiled images, using copy instead of blit!" << std::endl;
        supportsBlit = false;
    }

    return supportsBlit;
}

bool PhysicalDevice::supportSurface(Surface* surface, uint32_t queueFamilyIndex) {
    VkBool32 support;
    VULKAN_CHECK_RESULT(vkGetPhysicalDeviceSurfaceSupportKHR(m_handle, queueFamilyIndex, surface->handle(), &support), "Failed getting physical device surface support")
    return static_cast<bool>(support);
}

uint32_t PhysicalDevice::findQueueFamily(VkQueueFlags flags) {
    uint32_t i = 0;
    for (const auto& familyProperty : m_queueFamilyProperties) {
        if (familyProperty.queueCount > 0 && (familyProperty.queueFlags & flags)) {
            return i;
        }
        i++;
    }

    return -1;
}

uint32_t PhysicalDevice::findMemoryType(uint32_t typeFilter, VkMemoryPropertyFlags properties) {
    for (uint32_t i = 0; i < m_memoryProperties.memoryTypeCount; i++) {
        if ((typeFilter & (1 << i)) && (m_memoryProperties.memoryTypes[i].propertyFlags & properties) == properties) {
            return i;
        }
    }

    return -1;
}

}
