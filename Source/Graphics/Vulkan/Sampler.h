#pragma once
#include "Device/Devicer.h"

namespace Vulkan {

class Sampler : public Devicer<VkSampler> {

public:
    Sampler(const Device* device);
    ~Sampler();
    VkResult create() override;
    void destroy() override;

private:
    VkSamplerCreateInfo createInfo = {};
};

} // Vulkan
