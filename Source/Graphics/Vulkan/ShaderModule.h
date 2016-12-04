#pragma once
#include "Base/Handle.h"
#include "Device.h"

namespace Vulkan {

class ShaderModule : public Handle<VkShaderModule> {

public:
    ShaderModule(const Device* device, size_t codeSize, const uint32_t* pCode);
    ~ShaderModule();
    bool create() override;

private:
    const Device* device;
    VkShaderModuleCreateInfo createInfo = {};
};

} // Vulkan
