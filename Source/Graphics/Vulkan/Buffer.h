#pragma once
#include "Base/Handle.h"
#include "Device.h"

namespace Vulkan {

class Buffer : public Handle<VkBuffer> {

public:
    Buffer(const Device* device, VkBufferUsageFlagBits usage);
    ~Buffer();
    VkResult create() override;
    void setSize(VkDeviceSize size);
    VkDeviceSize getSize() const { return createInfo.size; }

private:
    const Device* device;
    VkBufferCreateInfo createInfo = {};
};

} // Vulkan
