#pragma once
#include "Device/Devicer.h"

namespace Vulkan {

class Fence : public Devicer<VkFence> {

public:
    Fence(const Device* device);
    ~Fence();
    VkResult create() override;
    void destroy() override;
    VkResult wait(uint32_t count);
    VkResult reset(uint32_t count);

private:
    VkFenceCreateInfo createInfo = {};
};

} // Vulkan
