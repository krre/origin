#pragma once
#include "Pipeline.h"

namespace Vulkan {

class GraphicsPipeline : public Pipeline {

public:
    GraphicsPipeline(Device* device);

    void create() override;

    void addVertexBindingDescription(VkVertexInputBindingDescription vertexBindingDescription);
    void addVertexAttributeDescription(VkVertexInputAttributeDescription vertexAttributeDescription);
    void addColorBlendAttachmentState(VkPipelineColorBlendAttachmentState colorBlendAttachmentState);
    void addViewport(VkViewport viewport);
    void addScissor(VkRect2D scissor);
    void addDynamicState(VkDynamicState dynamicState);

    void setPrimitiveTopology(VkPrimitiveTopology topology);
    void setPipelineLayout(VkPipelineLayout layout);
    void setRenderPass(VkRenderPass renderPass);

    VkPipelineBindPoint bindPoint() const override { return VK_PIPELINE_BIND_POINT_GRAPHICS; }

private:
    VkGraphicsPipelineCreateInfo m_createInfo = {};

    VkPipelineRasterizationStateCreateInfo m_rasterizationStateCreateInfo = {};
    VkPipelineMultisampleStateCreateInfo m_multisampleStateCreateInfo = {};
    VkPipelineInputAssemblyStateCreateInfo m_inputAssemblyStateCreateInfo = {};
    VkPipelineColorBlendStateCreateInfo m_colorBlendStateCreateInfo = {};
    VkPipelineDepthStencilStateCreateInfo m_depthStencilStateCreateInfo = {};
    VkPipelineVertexInputStateCreateInfo m_vertexInputStateCreateInfo = {};
    VkPipelineViewportStateCreateInfo m_viewportStateCreateInfo = {};
    VkPipelineDynamicStateCreateInfo m_dynamicStateCreateInfo = {};
    VkPipelineTessellationStateCreateInfo m_tessellationStateCreateInfo = {};

    std::vector<VkVertexInputBindingDescription> m_vertexBindingDescriptions;
    std::vector<VkVertexInputAttributeDescription> m_vertexAttributeDescriptions;
    std::vector<VkPipelineColorBlendAttachmentState> m_colorBlendAttachmentStates;
    std::vector<VkViewport> m_viewports;
    std::vector<VkRect2D> m_scissors;
    std::vector<VkDynamicState> m_dynamicStates;
};

}
