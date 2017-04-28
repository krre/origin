#pragma once
#include "Pipeline.h"
#include "Graphics/Vulkan/RenderPass.h"

namespace Vulkan {

class GraphicsPipeline : public Pipeline {

public:
    GraphicsPipeline(Device* device = nullptr);
    void addVertexBindingDescription(VkVertexInputBindingDescription vertexBindingDescription);
    void addVertexAttributeDescription(VkVertexInputAttributeDescription vertexAttributeDescription);
    void addColorBlendAttachmentState(VkPipelineColorBlendAttachmentState colorBlendAttachmentState);

    void addViewport(VkViewport viewport);
    void addScissor(VkRect2D scissor);

    void setPipelineLayout(VkPipelineLayout layout);
    void setRenderPass(VkRenderPass renderPass);
    void setBlendEnable(VkBool32 blendEnable);
    void setExtent(VkExtent2D extent);

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

    VkPipelineColorBlendAttachmentState colorBlendAttachmentState = {};

    VkViewport viewport = {};
    VkRect2D scissor = {};

    std::vector<VkVertexInputBindingDescription> vertexBindingDescriptions;
    std::vector<VkVertexInputAttributeDescription> vertexAttributeDescriptions;
    std::vector<VkPipelineColorBlendAttachmentState> colorBlendAttachmentStates;
    std::vector<VkViewport> viewports;
    std::vector<VkRect2D> scissors;
};

} // Vulkan
