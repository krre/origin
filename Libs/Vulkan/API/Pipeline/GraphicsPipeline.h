#pragma once
#include "Pipeline.h"

namespace Vulkan {

class GraphicsPipeline : public Pipeline {

public:
    GraphicsPipeline(Device* device);
    void addVertexBindingDescription(VkVertexInputBindingDescription vertexBindingDescription);
    void addVertexAttributeDescription(VkVertexInputAttributeDescription vertexAttributeDescription);
    void addColorBlendAttachmentState(VkPipelineColorBlendAttachmentState colorBlendAttachmentState);
    void addViewport(VkViewport viewport);
    void addScissor(VkRect2D scissor);
    void addDynamicState(VkDynamicState dynamicState);

    void setPipelineLayout(VkPipelineLayout layout);
    void setRenderPass(VkRenderPass renderPass);

    VkPipelineBindPoint getBindPoint() const override { return VK_PIPELINE_BIND_POINT_GRAPHICS; }
    void create() override;

private:
    VkGraphicsPipelineCreateInfo createInfo = {};

    VkPipelineRasterizationStateCreateInfo rasterizationStateCreateInfo = {};
    VkPipelineMultisampleStateCreateInfo multisampleStateCreateInfo = {};
    VkPipelineInputAssemblyStateCreateInfo inputAssemblyStateCreateInfo = {};
    VkPipelineColorBlendStateCreateInfo colorBlendStateCreateInfo = {};
    VkPipelineDepthStencilStateCreateInfo depthStencilStateCreateInfo = {};
    VkPipelineVertexInputStateCreateInfo vertexInputStateCreateInfo = {};
    VkPipelineViewportStateCreateInfo viewportStateCreateInfo = {};
    VkPipelineDynamicStateCreateInfo dynamicStateCreateInfo = {};
    VkPipelineTessellationStateCreateInfo tessellationStateCreateInfo = {};

    std::vector<VkVertexInputBindingDescription> vertexBindingDescriptions;
    std::vector<VkVertexInputAttributeDescription> vertexAttributeDescriptions;
    std::vector<VkPipelineColorBlendAttachmentState> colorBlendAttachmentStates;
    std::vector<VkViewport> viewports;
    std::vector<VkRect2D> scissors;
    std::vector<VkDynamicState> dynamicStates;
};

} // Vulkan
