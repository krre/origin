#pragma once
#include "Base/Handle.h"
#include "Device/Devicer.h"

namespace Origin {

namespace Vulkan {

class Fence : public Handle<VkFence>, public Devicer {

public:
    Fence(Device* device);
    ~Fence();
    void create() override;
    void destroy() override;
    VkResult wait();
    VkResult reset();
    void setSignaledBit();

private:
    VkFenceCreateInfo createInfo = {};
};

} // Vulkan

} // Origin
