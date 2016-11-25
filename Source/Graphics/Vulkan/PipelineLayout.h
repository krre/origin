#pragma once
#include "VkObject.h"
#include "Device.h"

namespace Vulkan {

class PipelineLayout : public VkObject {

public:
    PipelineLayout(const Device* device);
    ~PipelineLayout();
    VkPipelineLayout getHandle() const { return handle; }
    bool isValid() const { return handle != VK_NULL_HANDLE; }

private:
    VkPipelineLayout handle = VK_NULL_HANDLE;
    const Device* device;
};

} // Vulkan
