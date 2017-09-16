#include "PhysicalDevice.h"
#include "Graphics/Render/Vulkan/Wrapper/Instance.h"
#include "Graphics/Render/Vulkan/Wrapper/Surface.h"
#include "Graphics/Render/Vulkan/Wrapper/Swapchain.h"

using namespace Vulkan;

PhysicalDevice::PhysicalDevice(VkPhysicalDevice physicalDevice) {
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

    for (const auto& format : depthFormats) {
        VkFormatProperties formatProps;
        vkGetPhysicalDeviceFormatProperties(handle, format, &formatProps);
        // Format must support depth stencil attachment for optimal tiling
        if (formatProps.optimalTilingFeatures & VK_FORMAT_FEATURE_DEPTH_STENCIL_ATTACHMENT_BIT) {
            return format;
        }
    }

    return VK_FORMAT_UNDEFINED;
}

bool PhysicalDevice::getSupportBlit() {
    // Get format properties for the swapchain color format
    VkFormatProperties formatProps;
    bool supportsBlit = true;

    // Check blit support for source and destination

    // Check if the device supports blitting from optimal images (the swapchain images are in optimal format)
    vkGetPhysicalDeviceFormatProperties(handle, Instance::get()->getSurface()->getSwapchain()->getImageFormat(), &formatProps);
    if (!(formatProps.optimalTilingFeatures & VK_FORMAT_FEATURE_BLIT_SRC_BIT)) {
//        std::cerr << "Device does not support blitting from optimal tiled images, using copy instead of blit!" << std::endl;
        supportsBlit = false;
    }

    // Check if the device supports blitting to linear images
    vkGetPhysicalDeviceFormatProperties(handle, VK_FORMAT_R8G8B8A8_UNORM, &formatProps);
    if (!(formatProps.linearTilingFeatures & VK_FORMAT_FEATURE_BLIT_DST_BIT)) {
//        std::cerr << "Device does not support blitting to linear tiled images, using copy instead of blit!" << std::endl;
        supportsBlit = false;
    }

    return supportsBlit;
}

uint32_t PhysicalDevice::findQueue(VkQueueFlags flags) {
    uint32_t i = 0;
    for (const auto& familyProperty : queueFamilyProperties) {
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
