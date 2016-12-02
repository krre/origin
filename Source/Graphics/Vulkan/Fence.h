#pragma once
#include "VkCreatableObject.h"
#include "Device.h"

namespace Vulkan {

class Fence : public VkCreatableObject<VkFence> {

public:
    Fence(const Device* device);
    ~Fence();
    void create() override;
    VkResult wait(uint32_t count);
    VkResult reset(uint32_t count);

private:
    const Device* device;
    VkFenceCreateInfo createInfo = {};
};

} // Vulkan
