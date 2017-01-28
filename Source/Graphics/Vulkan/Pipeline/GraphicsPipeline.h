#pragma once
#include "Pipeline.h"
#include "../RenderPass.h"
#include "PipelineCache.h"

namespace Vulkan {

class GraphicsPipeline : public Pipeline {

public:
    GraphicsPipeline(const Device* device);
    void setExtent(VkExtent2D extent);
    void setPipelineLayout(const PipelineLayout* pipelineLayout);
    void setRenderPass(const RenderPass* renderPass);
    void setVertexBindingDescriptions(const std::vector<VkVertexInputBindingDescription>& vertexBindingDescriptions);
    void setVertexAttributeDescriptions(const std::vector<VkVertexInputAttributeDescription>& vertexAttributeDescriptions);
    void setPipelineCache(PipelineCache* pipelineCache);
    VkResult create() override;

private:
    const RenderPass* renderPass;
    VkGraphicsPipelineCreateInfo createInfo = {};
    VkPipelineVertexInputStateCreateInfo vertexInputInfo = {};
    std::vector<VkVertexInputBindingDescription> vertexBindingDescriptions;
    std::vector<VkVertexInputAttributeDescription> vertexAttributeDescriptions;
    VkExtent2D extent;
    PipelineCache* pipelineCache = nullptr;
};

} // Vulkan
