#pragma once
#include "CreatableObject.h"
#include "Device.h"

namespace Vulkan {

class Fence : public CreatableObject<VkFence> {

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
