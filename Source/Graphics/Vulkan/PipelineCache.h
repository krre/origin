#pragma once
#include "Base/CreatableObject.h"
#include "Device.h"

namespace Vulkan {

class PipelineCache : public CreatableObject<VkPipelineCache> {

public:
    PipelineCache(const Device* device);
    ~PipelineCache();
    bool create() override;

private:
    const Device* device;
    VkPipelineCacheCreateInfo createInfo = {};
};

} // Vulkan
