#pragma once
#include "VulkanObject.h"
#include "Instance.h"
#include <vulkan/vulkan.h>

namespace Vulkan {

class PhysicalDevice : public VulkanObject {

public:
    PhysicalDevice(const Instance* instance);
    uint32_t getCount() const { return count; }

private:
    const Instance* instance;
    uint32_t count = 0;
};

} // Vulkan
