#pragma once
#include "Base/Handle.h"
#include "Device.h"

namespace Vulkan {

class DescriptorPool : public Handle<VkPipelineLayout> {

public:
    DescriptorPool(const Device* device);
    ~DescriptorPool();
    VkResult create() override;

private:
    const Device* device;
    VkDescriptorPoolCreateInfo createInfo = {};
};

} // Vulkan
