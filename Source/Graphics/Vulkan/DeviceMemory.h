#pragma once
#include "Base/Handle.h"
#include "Device.h"

namespace Vulkan {

class DeviceMemory : public Handle<VkDeviceMemory> {

public:
    DeviceMemory(const Device* device);
    ~DeviceMemory();
    VkResult create() {}
    VkResult allocate();
    void setAllocationSize(VkDeviceSize allocationSize);
    void setMemoryTypeIndex(uint32_t index);

private:
    const Device* device;
    VkMemoryAllocateInfo allocateInfo;
};

} // Vulkan
