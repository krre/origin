#pragma once
#include "CreatableObject.h"
#include "Device.h"

namespace Vulkan {

class ShaderModule : public CreatableObject<VkShaderModule> {

public:
    ShaderModule(const Device* device, size_t codeSize, const uint32_t* pCode);
    ~ShaderModule();
    void create() override;

private:
    const Device* device;
    VkShaderModuleCreateInfo createInfo = {};
};

} // Vulkan
