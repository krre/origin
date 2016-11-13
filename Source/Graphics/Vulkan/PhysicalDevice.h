#pragma once
#include "VulkanObject.h"
#include "Instance.h"
#include <vulkan/vulkan.h>

namespace Vulkan {

class PhysicalDevice : public VulkanObject {

public:
    PhysicalDevice(const Instance* instance);

private:
    const Instance* instance;
};

} // Vulkan
