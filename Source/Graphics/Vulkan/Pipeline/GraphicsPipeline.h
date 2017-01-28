#pragma once
#include "Pipeline.h"
#include "../RenderPass.h"
#include "PipelineCache.h"

namespace Vulkan {

class GraphicsPipeline : public Pipeline {

public:
    GraphicsPipeline(const Device* device);
    void setExtent(VkExtent2D extent);
    void setRenderPass(const RenderPass* renderPass);
    void setVertexBindingDescriptions(const std::vector<VkVertexInputBindingDescription>& vertexBindingDescriptions);
    void setVertexAttributeDescriptions(const std::vector<VkVertexInputAttributeDescription>& vertexAttributeDescriptions);
    void setPipelineCache(const PipelineCache* pipelineCache);
    VkResult create() override;

private:
    const RenderPass* renderPass = nullptr;
    const PipelineCache* pipelineCache = nullptr;
    VkGraphicsPipelineCreateInfo createInfo = {};
    VkPipelineVertexInputStateCreateInfo vertexInputInfo = {};
    std::vector<VkVertexInputBindingDescription> vertexBindingDescriptions;
    std::vector<VkVertexInputAttributeDescription> vertexAttributeDescriptions;
    VkExtent2D extent;
};

} // Vulkan
