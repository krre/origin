#pragma once
#include "../Base/Collection.h"
#include "../Instance.h"
#include "PhysicalDevice.h"
#include <vector>
#include <map>

namespace Vulkan {

class PhysicalDevices : public Collection<VkPhysicalDevice> {

public:
    PhysicalDevices(VkInstance instance);
    PhysicalDevice* findDevice(VkPhysicalDeviceType type);
    void dumpDevices();
    void destroy() override {}

private:
    std::vector<std::shared_ptr<PhysicalDevice>> devices;
};

} // Vulkan
