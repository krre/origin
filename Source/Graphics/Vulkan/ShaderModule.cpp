#include "ShaderModule.h"

using namespace Vulkan;

ShaderModule::ShaderModule(const Device* device, size_t codeSize, const uint32_t* pCode) : device(device) {
    createInfo.sType = VK_STRUCTURE_TYPE_SHADER_MODULE_CREATE_INFO;
    createInfo.codeSize = codeSize;
    createInfo.pCode = pCode;
}

ShaderModule::~ShaderModule() {
    vkDestroyShaderModule(device->getHandle(), handle, nullptr);
}

bool ShaderModule::create() {
    return checkError(vkCreateShaderModule(device->getHandle(), &createInfo, nullptr, &handle), "Failed to create shader module");
}
