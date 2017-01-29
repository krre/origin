#pragma once
#include "Base/Handle.h"
#include "Device/Devicer.h"

namespace Vulkan {

class ShaderModule : public Handle<VkShaderModule>, public Devicer {

public:
    ShaderModule(const Device* device, size_t codeSize, const uint32_t* pCode);
    ~ShaderModule();
    VkResult create() override;
    void destroy() override;

private:
    VkShaderModuleCreateInfo createInfo = {};
};

} // Vulkan
