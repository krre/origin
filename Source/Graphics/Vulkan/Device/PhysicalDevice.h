#pragma once
#include "../Base/Handle.h"

namespace Vulkan {

class PhysicalDevice : public Handle<VkPhysicalDevice> {

public:
    PhysicalDevice(VkPhysicalDevice physicalDevice);
    VkResult create() override {}

private:

};

} // Vulkan
