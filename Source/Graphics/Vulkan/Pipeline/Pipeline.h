#pragma once
#include "../Base/Handle.h"
#include "../Device/Device.h"
#include "../ShaderModule.h"
#include "PipelineLayout.h"

namespace Vulkan {

class Pipeline : public Handle<VkPipeline> {

public:
    Pipeline(const Device* device);
    ~Pipeline();
    VkResult addShaderCode(VkShaderStageFlagBits stage, const char* entryPoint, size_t size, const uint32_t* code);
    void setPipelineLayout(const PipelineLayout* pipelineLayout);

protected:
    const Device* device;
    const PipelineLayout* pipelineLayout;
    std::map<VkShaderStageFlagBits, std::shared_ptr<Vulkan::ShaderModule>> shaderModules;
    std::vector<VkPipelineShaderStageCreateInfo> shaderStages;
};

} // Vulkan
