#pragma once
#include "VkCreatableObject.h"
#include "Device.h"

namespace Vulkan {

class DeviceMemory : public VkCreatableObject<VkDeviceMemory> {

public:
    DeviceMemory(const Device* device);
    ~DeviceMemory();
    void create() override;

private:
    const Device* device;
    VkMemoryAllocateInfo allocateInfo;
};

} // Vulkan
