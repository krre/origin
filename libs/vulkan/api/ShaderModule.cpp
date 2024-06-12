#include "ShaderModule.h"

namespace Vulkan {

ShaderModule::ShaderModule(Device* device, size_t codeSize, const uint32_t* pCode) : Devicer(device) {
    m_createInfo.sType = VK_STRUCTURE_TYPE_SHADER_MODULE_CREATE_INFO;
    m_createInfo.codeSize = codeSize;
    m_createInfo.pCode = pCode;
}

ShaderModule::~ShaderModule() {
    vkDestroyShaderModule(m_device->handle(), m_handle, nullptr);
}

void ShaderModule::create() {
    VULKAN_CHECK_RESULT(vkCreateShaderModule(m_device->handle(), &m_createInfo, nullptr, &m_handle), "Failed to create shader module");
}

}
