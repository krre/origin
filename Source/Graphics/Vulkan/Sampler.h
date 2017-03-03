#pragma once
#include "Base/Handle.h"
#include "Device/Devicer.h"

namespace Vulkan {

class Sampler : public Handle<VkSampler>, public Devicer {

public:
    Sampler(const Device* device);
    ~Sampler();
    VkResult create() override;
    void destroy() override;

    VkSamplerCreateInfo createInfo = {};
};

} // Vulkan
