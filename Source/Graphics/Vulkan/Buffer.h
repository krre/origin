#pragma once
#include "Base/Handle.h"
#include "Device.h"

namespace Vulkan {

class Buffer : public Handle<VkBuffer> {

public:
    Buffer(const Device* device);
    ~Buffer();
    VkResult create() override;
    void setSize(VkDeviceSize size);
    void setUsage(VkBufferUsageFlags usage);

private:
    const Device* device;
    VkBufferCreateInfo createInfo;
};

} // Vulkan
