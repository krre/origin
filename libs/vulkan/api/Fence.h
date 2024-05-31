#pragma once
#include "base/Handle.h"
#include "device/Devicer.h"

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

}
