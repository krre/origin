#include "ShaderModule.h"

using namespace Vulkan;

ShaderModule::ShaderModule(const Device* device, size_t codeSize, const uint32_t* pCode) : device(device) {
    VkShaderModuleCreateInfo createInfo = {};
    createInfo.sType = VK_STRUCTURE_TYPE_SHADER_MODULE_CREATE_INFO;
    createInfo.codeSize = codeSize;
    createInfo.pCode = pCode;
    result = vkCreateShaderModule(device->getHandle(), &createInfo, nullptr, &handle);
}

ShaderModule::~ShaderModule() {
    if (handle != VK_NULL_HANDLE) {
        vkDestroyShaderModule(device->getHandle(), handle, nullptr);
    }
}
