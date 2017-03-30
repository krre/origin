#pragma once
#include "../Base/Handle.h"
#include "../Device/Devicer.h"
#include "../ShaderModule.h"
#include "PipelineLayout.h"
#include "PipelineCache.h"
#include <map>
#include <memory>

namespace Vulkan {

class Pipeline : public Handle<VkPipeline>, public Devicer {

public:
    Pipeline(const Device* device) : Devicer(device) {}
    ~Pipeline();
    void destroy() override;
    void addShaderCode(VkShaderStageFlagBits stage, size_t size, const uint32_t* code, const char* entryPoint = "main");
    void setPipelineCache(VkPipelineCache pipelineCache);
    virtual VkPipelineBindPoint getBindPoint() const = 0;

protected:
    VkPipelineCache pipelineCache = VK_NULL_HANDLE;
    std::map<VkShaderStageFlagBits, std::shared_ptr<Vulkan::ShaderModule>> shaderModules;
    std::vector<VkPipelineShaderStageCreateInfo> shaderStages;
};

} // Vulkan
