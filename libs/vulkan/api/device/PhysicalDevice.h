#pragma once
#include "../base/Handle.h"
#include <vector>

namespace Vulkan {

class Surface;

class PhysicalDevice : public Handle<VkPhysicalDevice> {
public:
    PhysicalDevice(VkPhysicalDevice physicalDevice);

    void create() override {}

    VkPhysicalDeviceProperties properties() const;
    VkPhysicalDeviceFeatures features() const;
    VkPhysicalDeviceMemoryProperties memoryProperties();
    std::vector<VkQueueFamilyProperties> queueFamilyProperties() const;

    VkFormat supportedDepthFormat();
    bool supportBlit(VkFormat format);
    bool supportSurface(Surface* surface, uint32_t queueFamilyIndex);

    uint32_t findQueueFamily(VkQueueFlags flags);
    uint32_t findMemoryType(uint32_t typeFilter, VkMemoryPropertyFlags properties);
};

}
