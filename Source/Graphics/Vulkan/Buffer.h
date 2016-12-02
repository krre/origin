#pragma once
#include "CreatableObject.h"
#include "Device.h"

namespace Vulkan {

class Buffer : public CreatableObject<VkBuffer> {

public:
    Buffer(const Device* device);
    ~Buffer();
    void create() override;
    void setSize(VkDeviceSize size);
    void setUsage(VkBufferUsageFlags usage);

private:
    const Device* device;
    VkBufferCreateInfo createInfo;
};

} // Vulkan