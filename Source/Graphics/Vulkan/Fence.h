#pragma once
#include "Base/Handle.h"
#include "Device/Device.h"

namespace Vulkan {

class Fence : public Handle<VkFence> {

public:
    Fence(const Device* device);
    ~Fence();
    VkResult create() override;
    void destroy() override;
    VkResult wait(uint32_t count);
    VkResult reset(uint32_t count);

private:
    const Device* device;
    VkFenceCreateInfo createInfo = {};
};

} // Vulkan
