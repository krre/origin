#pragma once
#include <vulkan/vulkan.h>
#include <vector>
#include <memory>

namespace Vulkan {

class Instance;
class PhysicalDevice;

class PhysicalDevices {

public:
    PhysicalDevices(Instance* instance);
    size_t count() const { return devices.size(); }
    PhysicalDevice* physicalDevice(size_t i) const { return devices.at(i).get(); }
    PhysicalDevice* findDevice(VkPhysicalDeviceType type);
    void dumpDevices();

private:
    std::vector<std::unique_ptr<PhysicalDevice>> devices;
};

}
