#pragma once
#include "VkObject.h"
#include "Device.h"

namespace Vulkan {

enum class PipelineType {
    Compute,
    Graphics
};

class Pipeline : public VkObject {

public:
    Pipeline(PipelineType type, const Device* device);
    ~Pipeline();
    VkPipeline getHandle() const { return handle; }
    bool isValid() const { return handle != VK_NULL_HANDLE; }
    PipelineType getType() const { return type; }

private:
    VkPipeline handle = VK_NULL_HANDLE;
    const Device* device;
    PipelineType type;
};

} // Vulkan
