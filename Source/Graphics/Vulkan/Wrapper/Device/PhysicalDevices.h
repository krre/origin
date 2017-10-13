#pragma once
#include "Graphics/Vulkan/Wrapper/Base/Collection.h"
#include <vulkan/vulkan.hpp>
#include <vector>

namespace Vulkan {

class Instance;
class PhysicalDevice;

class PhysicalDevices {

public:
    PhysicalDevices(Instance* instance);
    size_t getCount() const { return devices.size(); }
    PhysicalDevice* getPhysicalDevice(size_t i) const { return devices.at(i).get(); }
    PhysicalDevice* findDevice(VkPhysicalDeviceType type);
    void dumpDevices();

private:
    std::vector<std::unique_ptr<PhysicalDevice>> devices;
};

} // Vulkan
