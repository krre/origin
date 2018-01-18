#pragma once
#include "Graphics/Vulkan/Base/Handle.h"
#include "Graphics/Vulkan/Device/Devicer.h"

namespace Origin {

namespace Vulkan {

class PipelineCache : public Handle<VkPipelineCache>, public Devicer {

public:
    PipelineCache(Device* device);
    ~PipelineCache();
    void create() override;
    void destroy() override;

private:
    VkPipelineCacheCreateInfo createInfo = {};
};

} // Vulkan

} // Origin
