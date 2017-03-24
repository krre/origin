#pragma once
#include "Base/Handle.h"
#include "Device/Devicer.h"

namespace Vulkan {

class ShaderModule : public Handle<VkShaderModule>, public Devicer {

public:
    ShaderModule(const Device* device, size_t codeSize, const uint32_t* pCode);
    ~ShaderModule();
    void create() override;
    void destroy() override;

    VkShaderModuleCreateInfo createInfo = {};

private:

};

} // Vulkan
