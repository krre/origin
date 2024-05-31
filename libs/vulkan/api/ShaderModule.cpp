#include "ShaderModule.h"

namespace Vulkan {

ShaderModule::ShaderModule(Device* device, size_t codeSize, const uint32_t* pCode) : Devicer(device) {
    createInfo.sType = VK_STRUCTURE_TYPE_SHADER_MODULE_CREATE_INFO;
    createInfo.codeSize = codeSize;
    createInfo.pCode = pCode;
}

ShaderModule::~ShaderModule() {
    destroy();
}

void ShaderModule::create() {
    VULKAN_CHECK_RESULT(vkCreateShaderModule(m_device->handle(), &createInfo, nullptr, &m_handle), "Failed to create shader module");
}

void ShaderModule::destroy() {
    VULKAN_DESTROY_HANDLE(vkDestroyShaderModule(m_device->handle(), m_handle, nullptr))
}

}
