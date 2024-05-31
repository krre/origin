#pragma once
#include "base/Handle.h"
#include "device/Devicer.h"

namespace Vulkan {

class ShaderModule : public Handle<VkShaderModule>, public Devicer {

public:
    ShaderModule(Device* device, size_t codeSize, const uint32_t* pCode);
    ~ShaderModule();
    void create() override;
    void destroy() override;

private:
    VkShaderModuleCreateInfo createInfo = {};

};

}
