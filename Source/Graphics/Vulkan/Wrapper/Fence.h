#pragma once
#include "Base/Handle.h"
#include "Device/Devicer.h"

namespace Vulkan {

class Fence : public Handle<VkFence>, public Devicer {

public:
    Fence(Device* device);
    ~Fence();
    void create() override;
    void destroy() override;
    VkResult wait(uint32_t count);
    VkResult reset(uint32_t count);

private:
    VkFenceCreateInfo createInfo = {};
};

} // Vulkan
