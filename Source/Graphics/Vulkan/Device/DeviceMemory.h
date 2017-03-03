#pragma once
#include "../Base/Handle.h"
#include "Devicer.h"

namespace Vulkan {

class DeviceMemory : public Handle<VkDeviceMemory>, public Devicer {

public:
    DeviceMemory(const Device* device);
    ~DeviceMemory();
    VkResult create() override {}
    void destroy() override;
    VkResult allocate(VkDeviceSize size);
    void setMemoryTypeIndex(uint32_t index);
    VkResult map(VkDeviceSize count, VkDeviceSize offset, void** data);
    void unmap();

    VkMemoryAllocateInfo allocateInfo = {};
};

} // Vulkan
