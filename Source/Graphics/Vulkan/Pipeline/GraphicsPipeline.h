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
    void setBlendEnable(bool blendEnable);
    VkResult create() override;

    VkGraphicsPipelineCreateInfo createInfo = {};

private:
    VkPipelineVertexInputStateCreateInfo vertexInputInfo = {};
    std::vector<VkVertexInputBindingDescription> vertexBindingDescriptions;
    std::vector<VkVertexInputAttributeDescription> vertexAttributeDescriptions;
    VkExtent2D extent;
    bool blendEnable = false;
};

} // Vulkan
