#pragma once
#include "../Base/Devicer.h"

namespace Vulkan {

class DeviceMemory : public Devicer<VkDeviceMemory> {

public:
    DeviceMemory(const Device* device);
    ~DeviceMemory();
    VkResult create() override {}
    void destroy() override;
    VkResult allocate(VkDeviceSize size);
    void setMemoryTypeIndex(uint32_t index);
    VkResult map(VkDeviceSize count, VkDeviceSize offset, void** data);
    void unmap();

private:
    VkMemoryAllocateInfo allocateInfo = {};
};

} // Vulkan
