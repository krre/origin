#pragma once
#include "VkObject.h"
#include "Device.h"

namespace Vulkan {

class ShaderModule : public VkObject {

public:
    ShaderModule(const Device* device, size_t codeSize, const uint32_t* pCode);
    ~ShaderModule();
    VkShaderModule getHandle() const { return handle; }
    bool isValid() const { return handle != VK_NULL_HANDLE; }

private:
    VkShaderModule handle = VK_NULL_HANDLE;
    const Device* device;
};

} // Vulkan
