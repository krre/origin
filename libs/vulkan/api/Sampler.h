#pragma once
#include "base/Handle.h"
#include "device/Devicer.h"

namespace Vulkan {

class Sampler : public Handle<VkSampler>, public Devicer {
public:
    Sampler(Device* device);
    ~Sampler();

    void create() override;

private:
    VkSamplerCreateInfo m_createInfo = {};
};

}
