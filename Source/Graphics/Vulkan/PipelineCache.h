#pragma once
#include "VkCreatableObject.h"
#include "Device.h"

namespace Vulkan {

class PipelineCache : public VkCreatableObject<VkPipelineCache> {

public:
    PipelineCache(const Device* device);
    ~PipelineCache();
    void create() override;

private:
    const Device* device;
    VkPipelineCacheCreateInfo createInfo = {};
};

} // Vulkan
