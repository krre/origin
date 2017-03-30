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
    void addColorBlendAttachment(VkPipelineColorBlendAttachmentState colorBlendAttachment);
    void setPipelineLayout(VkPipelineLayout layout);
    void setRenderPass(VkRenderPass renderPass);
    void create() override;

    VkGraphicsPipelineCreateInfo createInfo = {};
    VkPipelineInputAssemblyStateCreateInfo inputAssembly = {};
    VkPipelineRasterizationStateCreateInfo rasterizer = {};
    VkPipelineMultisampleStateCreateInfo multisampling = {};
    VkViewport viewport = {};
    VkRect2D scissor = {};
    VkPipelineColorBlendAttachmentState colorBlendAttachment = {};
    VkPipelineColorBlendStateCreateInfo colorBlending = {};

private:
    VkPipelineVertexInputStateCreateInfo vertexInputInfo = {};
    std::vector<VkVertexInputBindingDescription> vertexBindingDescriptions;
    std::vector<VkVertexInputAttributeDescription> vertexAttributeDescriptions;
    std::vector<VkViewport> viewports;
    std::vector<VkRect2D> scissors;
    std::vector<VkPipelineColorBlendAttachmentState> colorBlendAttachments;
};

} // Vulkan
