#pragma once
#include "Base/Handle.h"
#include "Device.h"

namespace Vulkan {

class DeviceMemory : public Handle<VkDeviceMemory> {

public:
    DeviceMemory(const Device* device);
    ~DeviceMemory();
    VkResult create() {}
    VkResult allocate(VkDeviceSize size);
    void setMemoryTypeIndex(uint32_t index);
    void map(VkDeviceSize count, VkDeviceSize offset, const unsigned char* data);
    void unmap();

private:
    const Device* device;
    VkMemoryAllocateInfo allocateInfo = {};
};

} // Vulkan
