#pragma once
#include "../Base/Collection.h"
#include "../Instance.h"
#include "PhysicalDevice.h"
#include <vector>
#include <map>

namespace Vulkan {

class PhysicalDevices : public Collection<VkPhysicalDevice> {

public:
    PhysicalDevices(const Instance* instance);
    PhysicalDevice* findDevice(VkPhysicalDeviceType type);
    void dumpDevices();
    void destroy() override {}

private:
    const Instance* instance;
    std::vector<std::shared_ptr<PhysicalDevice>> devices;
};

} // Vulkan
