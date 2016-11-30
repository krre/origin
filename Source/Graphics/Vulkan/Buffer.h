#pragma once
#include "VkCreatableObject.h"
#include "Device.h"

namespace Vulkan {

class Buffer : public VkCreatableObject<VkBuffer> {

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
