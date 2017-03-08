#pragma once
#include "Pipeline.h"
#include "../RenderPass.h"

namespace Vulkan {

class GraphicsPipeline : public Pipeline {

public:
    GraphicsPipeline(const Device* device);
    void setExtent(VkExtent2D extent);
    void addVertexBindingDescription(VkVertexInputBindingDescription vertexBindingDescription);
    void addVertexAttributeDescription(VkVertexInputAttributeDescription vertexAttributeDescription);
    void addViewport(VkViewport viewport);
    void setBlendEnable(bool blendEnable);
    VkResult create() override;

    VkGraphicsPipelineCreateInfo createInfo = {};
    VkViewport viewport = {};

private:
    VkPipelineVertexInputStateCreateInfo vertexInputInfo = {};
    std::vector<VkVertexInputBindingDescription> vertexBindingDescriptions;
    std::vector<VkVertexInputAttributeDescription> vertexAttributeDescriptions;
    std::vector<VkViewport> viewports;
    VkExtent2D extent;
    bool blendEnable = false;
};

} // Vulkan
