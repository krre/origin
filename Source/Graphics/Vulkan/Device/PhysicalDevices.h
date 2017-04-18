#pragma once
#include "Graphics/Vulkan/Base/Collection.h"
#include <vulkan/vulkan.hpp>
#include <vector>

namespace Vulkan {

class PhysicalDevice;

class PhysicalDevices : public Collection<VkPhysicalDevice> {

public:
    PhysicalDevices(VkInstance instance);
    PhysicalDevice* findDevice(VkPhysicalDeviceType type);
    void dumpDevices();
    void destroy() override {}

private:
    std::vector<std::unique_ptr<PhysicalDevice>> devices;
};

} // Vulkan
