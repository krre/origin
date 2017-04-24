#pragma once
#include "Base/Handle.h"
#include "Device/Devicer.h"

namespace Vulkan {

class ShaderModule : public Handle<VkShaderModule>, public Devicer {

public:
    ShaderModule(size_t codeSize, const uint32_t* pCode, Device* device = nullptr);
    ~ShaderModule();
    void create() override;
    void destroy() override;

private:
    VkShaderModuleCreateInfo createInfo = {};

};

} // Vulkan
