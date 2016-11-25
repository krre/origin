#pragma once
#include "VkObject.h"
#include "Device.h"

namespace Vulkan {

class PipelineCache : public VkObject {

public:
    PipelineCache(const Device* device);
    ~PipelineCache();
    VkPipelineCache getHandle() const { return handle; }
    bool isValid() const { return handle != VK_NULL_HANDLE; }

private:
    VkPipelineCache handle = VK_NULL_HANDLE;
    const Device* device;
};

} // Vulkan
