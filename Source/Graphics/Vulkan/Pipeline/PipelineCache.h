#pragma once
#include "../Device/Devicer.h"

namespace Vulkan {

class PipelineCache : public Devicer<VkPipelineCache> {

public:
    PipelineCache(const Device* device);
    ~PipelineCache();
    VkResult create() override;
    void destroy() override;

private:
    VkPipelineCacheCreateInfo createInfo = {};
};

} // Vulkan
