#include "ShaderModule.h"

using namespace Vulkan;

ShaderModule::ShaderModule(Device* device, size_t codeSize, const uint32_t* pCode) : Devicer(device) {
    createInfo.sType = VK_STRUCTURE_TYPE_SHADER_MODULE_CREATE_INFO;
    createInfo.codeSize = codeSize;
    createInfo.pCode = pCode;
}

ShaderModule::~ShaderModule() {
    destroy();
}

void ShaderModule::create() {
    VULKAN_CHECK_RESULT(vkCreateShaderModule(device->getHandle(), &createInfo, nullptr, &handle), "Failed to create shader module");
}

void ShaderModule::destroy() {
    VULKAN_DESTROY_HANDLE(vkDestroyShaderModule(device->getHandle(), handle, nullptr))
}
