#pragma once
#include "../base/Handle.h"
#include <vector>

namespace Vulkan {

class Surface;

class PhysicalDevice : public Handle<VkPhysicalDevice> {
public:
    PhysicalDevice(VkPhysicalDevice physicalDevice);

    void create() override {}

    const VkPhysicalDeviceProperties& properties() const { return m_properties; }
    const VkPhysicalDeviceFeatures& features() const { return m_features; }
    const VkPhysicalDeviceMemoryProperties& memoryProperties() const { return m_memoryProperties; }
    const std::vector<VkQueueFamilyProperties>& queueFamilyProperties() const { return m_queueFamilyProperties; }
    VkFormat supportedDepthFormat();
    bool supportBlit(VkFormat format);
    bool supportSurface(Surface* surface, uint32_t queueFamilyIndex);

    uint32_t findQueueFamily(VkQueueFlags flags);
    uint32_t findMemoryType(uint32_t typeFilter, VkMemoryPropertyFlags properties);

private:
    VkPhysicalDeviceProperties m_properties;
    VkPhysicalDeviceFeatures m_features;
    VkPhysicalDeviceMemoryProperties m_memoryProperties;
    std::vector<VkQueueFamilyProperties> m_queueFamilyProperties;
};

}
