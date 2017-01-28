#pragma once
#include "Device/Devicer.h"

namespace Vulkan {

class ShaderModule : public Devicer<VkShaderModule> {

public:
    ShaderModule(const Device* device, size_t codeSize, const uint32_t* pCode);
    ~ShaderModule();
    VkResult create() override;
    void destroy() override;

private:
    VkShaderModuleCreateInfo createInfo = {};
};

} // Vulkan
