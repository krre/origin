#pragma once
#include "VkObject.h"
#include "Device.h"

namespace Vulkan {

class Pipeline : public VkObject {

public:
    Pipeline(const Device* device);
    ~Pipeline();
    VkPipeline getHandle() const { return handle; }
    bool isValid() const { return handle != VK_NULL_HANDLE; }

private:
    VkPipeline handle = VK_NULL_HANDLE;
    const Device* device;
};

} // Vulkan
