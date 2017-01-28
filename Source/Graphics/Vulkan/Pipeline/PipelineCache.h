#pragma once
#include "../Base/Handle.h"
#include "../Device/Device.h"

namespace Vulkan {

class PipelineCache : public Handle<VkPipelineCache> {

public:
    PipelineCache(const Device* device);
    ~PipelineCache();
    VkResult create() override;
    void destroy() override;

private:
    const Device* device;
    VkPipelineCacheCreateInfo createInfo = {};
};

} // Vulkan
