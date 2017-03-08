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
    void addScissor(VkRect2D scissor);
    void setBlendEnable(bool blendEnable);
    VkResult create() override;

    VkGraphicsPipelineCreateInfo createInfo = {};
    VkViewport viewport = {};
    VkRect2D scissor = {};

private:
    VkPipelineVertexInputStateCreateInfo vertexInputInfo = {};
    std::vector<VkVertexInputBindingDescription> vertexBindingDescriptions;
    std::vector<VkVertexInputAttributeDescription> vertexAttributeDescriptions;
    std::vector<VkViewport> viewports;
    std::vector<VkRect2D> scissors;
    bool blendEnable = false;
};

} // Vulkan
