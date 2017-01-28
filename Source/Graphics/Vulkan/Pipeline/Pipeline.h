#pragma once
#include "../Base/Devicer.h"
#include "../ShaderModule.h"
#include "PipelineLayout.h"
#include "PipelineCache.h"

namespace Vulkan {

class Pipeline : public Devicer<VkPipeline> {

public:
    Pipeline(const Device* device) : Devicer(device) {}
    ~Pipeline();
    void destroy() override;
    VkResult addShaderCode(VkShaderStageFlagBits stage, const char* entryPoint, size_t size, const uint32_t* code);
    void setPipelineLayout(const PipelineLayout* pipelineLayout);
    void setPipelineCache(const PipelineCache* pipelineCache);

protected:
    const PipelineLayout* pipelineLayout = nullptr;
    const PipelineCache* pipelineCache = nullptr;
    std::map<VkShaderStageFlagBits, std::shared_ptr<Vulkan::ShaderModule>> shaderModules;
    std::vector<VkPipelineShaderStageCreateInfo> shaderStages;
};

} // Vulkan
