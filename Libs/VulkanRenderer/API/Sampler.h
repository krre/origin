#pragma once
#include "Base/Handle.h"
#include "Device/Devicer.h"

namespace Vulkan {

class Sampler : public Handle<VkSampler>, public Devicer {

public:
    Sampler(Device* device);
    ~Sampler();
    void create() override;
    void destroy() override;

private:
    VkSamplerCreateInfo createInfo = {};
};

} // Vulkan
