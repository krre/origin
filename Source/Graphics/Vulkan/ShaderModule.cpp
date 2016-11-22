#include "ShaderModule.h"

using namespace Vulkan;

ShaderModule::ShaderModule(const Device* device) : device(device) {

}

ShaderModule::~ShaderModule() {
    if (handle != VK_NULL_HANDLE) {
        vkDestroyShaderModule(device->getHandle(), handle, nullptr);
    }
}
