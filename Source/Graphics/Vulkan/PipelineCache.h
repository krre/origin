#pragma once
#include "Base/Handle.h"
#include "Device.h"

namespace Vulkan {

class PipelineCache : public Handle<VkPipelineCache> {

public:
    PipelineCache(const Device* device);
    ~PipelineCache();
    bool create() override;

private:
    const Device* device;
    VkPipelineCacheCreateInfo createInfo = {};
};

} // Vulkan
