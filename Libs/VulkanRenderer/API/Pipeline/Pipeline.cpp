#include "Pipeline.h"
#include "../ShaderModule.h"

namespace Vulkan {

Pipeline::~Pipeline() {
    destroy();
}

void Pipeline::destroy() {
    VULKAN_DESTROY_HANDLE(vkDestroyPipeline(device->getHandle(), handle, nullptr))
}

void Pipeline::addShaderCode(VkShaderStageFlagBits stage, size_t size, const uint32_t* code, const char* entryPoint) {
    auto shaderModule = std::make_shared<ShaderModule>(device, size, code);
    shaderModule->create();
    shaderModules[stage] = shaderModule;
    VkPipelineShaderStageCreateInfo shaderStageInfo = {};
    shaderStageInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO;
    shaderStageInfo.stage = stage;
    shaderStageInfo.module = shaderModules[stage]->getHandle();
    shaderStageInfo.pName = entryPoint;
    shaderStages.push_back(shaderStageInfo);
}

void Pipeline::setPipelineCache(VkPipelineCache pipelineCache) {
    this->pipelineCache = pipelineCache;
}

} // Vulkan
