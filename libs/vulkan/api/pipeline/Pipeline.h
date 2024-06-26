#pragma once
#include "../base/Handle.h"
#include "../device/Devicer.h"
#include <map>
#include <memory>

namespace Vulkan {

class ShaderModule;

class Pipeline : public Handle<VkPipeline>, public Devicer {
public:
    Pipeline(Device* device) : Devicer(device) {}
    virtual ~Pipeline();

    void addShaderCode(VkShaderStageFlagBits stage, size_t size, const uint32_t* code, const char* entryPoint = "main");
    void setPipelineCache(VkPipelineCache pipelineCache);

    virtual VkPipelineBindPoint bindPoint() const = 0;

protected:
    VkPipelineCache m_pipelineCache = VK_NULL_HANDLE;
    std::map<VkShaderStageFlagBits, std::shared_ptr<Vulkan::ShaderModule>> m_shaderModules;
    std::vector<VkPipelineShaderStageCreateInfo> m_shaderStages;
};

}
