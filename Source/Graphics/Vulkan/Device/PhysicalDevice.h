#pragma once
#include "../Base/Handle.h"

namespace Vulkan {

class PhysicalDevice : public Handle<VkPhysicalDevice> {
    friend class PhysicalDevices;

public:
    PhysicalDevice(VkPhysicalDevice physicalDevice);
    VkResult create() override {}

private:

};

} // Vulkan
