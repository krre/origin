#pragma once
#include "VulkanObject.h"
#include "Instance.h"
#include <vulkan/vulkan.h>

namespace Vulkan {

class PhysicalDevice : public VulkanObject {

public:
    PhysicalDevice(Instance& instance);

private:
    Instance instance;
};

} // Vulkan
