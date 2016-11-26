#pragma once
#include "VkObject.h"
#include "Device.h"
#include "ShaderModule.h"
#include "PipelineLayout.h"
#include "RenderPass.h"

namespace Vulkan {

enum class PipelineType {
    Compute,
    Graphics
};

enum class ShaderType {
    Vertex,
    Fragment
};

class Pipeline : public VkObject {

public:
    Pipeline(PipelineType type, const Device* device);
    ~Pipeline();
    VkPipeline getHandle() const { return handle; }
    bool isValid() const { return handle != VK_NULL_HANDLE; }
    PipelineType getType() const { return type; }
    bool addShaderCode(ShaderType type, size_t size, const uint32_t* code);
    void setExtent(VkExtent2D extent) { this->extent = extent; }
    void setPipelineLayout(const PipelineLayout* pipelineLayout) { this->pipelineLayout = pipelineLayout; }
    void setRenderPass(const RenderPass* renderPass) { this->renderPass = renderPass; }
    void create();

private:
    VkPipeline handle = VK_NULL_HANDLE;
    const Device* device;
    PipelineType type;
    std::map<ShaderType, std::shared_ptr<Vulkan::ShaderModule>> shaderModules;
    VkExtent2D extent;
    const PipelineLayout* pipelineLayout;
    const RenderPass* renderPass;
};

} // Vulkan