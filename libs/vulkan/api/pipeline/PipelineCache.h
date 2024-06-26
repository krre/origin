#pragma once
#include "../base/Handle.h"
#include "../device/Devicer.h"

namespace Vulkan {

class PipelineCache : public Handle<VkPipelineCache>, public Devicer {
public:
    PipelineCache(Device* device);
    ~PipelineCache();

    void create() override;

private:
    VkPipelineCacheCreateInfo m_createInfo = {};
};

}
