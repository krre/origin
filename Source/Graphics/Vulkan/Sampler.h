#pragma once
#include "Base/Handle.h"
#include "Device/Device.h"

namespace Vulkan {

class Sampler : public Handle<VkSampler> {

public:
    Sampler(const Device* device);
    ~Sampler();
    VkResult create() override;

private:
    const Device* device;
    VkSamplerCreateInfo createInfo = {};
};

} // Vulkan
