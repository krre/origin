#pragma once
#include "Graphics/Render/Vulkan/Wrapper/Base/Handle.h"
#include "Graphics/Render/Vulkan/Wrapper/Device/Devicer.h"

namespace Vulkan {

class PipelineCache : public Handle<VkPipelineCache>, public Devicer {

public:
    PipelineCache(Device* device = nullptr);
    ~PipelineCache();
    void create() override;
    void destroy() override;

private:
    VkPipelineCacheCreateInfo createInfo = {};
};

} // Vulkan
