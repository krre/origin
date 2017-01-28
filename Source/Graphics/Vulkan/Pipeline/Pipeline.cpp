#include "Pipeline.h"

using namespace Vulkan;

Pipeline::Pipeline(const Device* device) : device(device) {

}

Pipeline::~Pipeline() {
    destroy();
}

void Pipeline::destroy() {
    VULKAN_DESTROY_HANDLE(vkDestroyPipeline(device->getHandle(), handle, nullptr))
}

VkResult Pipeline::addShaderCode(VkShaderStageFlagBits stage, const char* entryPoint, size_t size, const uint32_t* code) {
    std::shared_ptr<ShaderModule> shaderModule(new ShaderModule(device, size, code));
    VkResult result = shaderModule->create();
    if (result == VK_SUCCESS) {;
        shaderModules[stage] = shaderModule;
        VkPipelineShaderStageCreateInfo shaderStageInfo = {};
        shaderStageInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO;
        shaderStageInfo.stage = stage;
        shaderStageInfo.module = shaderModules[stage]->getHandle();
        shaderStageInfo.pName = entryPoint;
        shaderStages.push_back(shaderStageInfo);
    }
    return result;
}

void Pipeline::setPipelineLayout(const PipelineLayout* pipelineLayout) {
    this->pipelineLayout = pipelineLayout;
}

void Pipeline::setPipelineCache(const PipelineCache* pipelineCache) {
    this->pipelineCache = pipelineCache;
}
