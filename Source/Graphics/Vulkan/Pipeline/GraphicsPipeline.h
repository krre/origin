#pragma once
#include "Pipeline.h"
#include "Graphics/Vulkan/RenderPass.h"

namespace Vulkan {

class GraphicsPipeline : public Pipeline {

public:
    GraphicsPipeline(Device* device = nullptr);
    void setExtent(VkExtent2D extent);
    void addVertexBindingDescription(VkVertexInputBindingDescription vertexBindingDescription);
    void addVertexAttributeDescription(VkVertexInputAttributeDescription vertexAttributeDescription);
    void addViewport(VkViewport viewport);
    void addScissor(VkRect2D scissor);
    void addColorBlendAttachment(VkPipelineColorBlendAttachmentState colorBlendAttachment);
    void setPipelineLayout(VkPipelineLayout layout);
    void setRenderPass(VkRenderPass renderPass);
    void setBlendEnable(VkBool32 blendEnable);
    VkPipelineBindPoint getBindPoint() const override { return VK_PIPELINE_BIND_POINT_GRAPHICS; }
    void create() override;

    VkPipelineRasterizationStateCreateInfo rasterizer = {};
    VkPipelineMultisampleStateCreateInfo multisampling = {};
    VkViewport viewport = {};
    VkRect2D scissor = {};
    VkPipelineColorBlendAttachmentState colorBlendAttachment = {};
    VkPipelineColorBlendStateCreateInfo colorBlendState = {};
    VkPipelineDepthStencilStateCreateInfo depthStencilState = {};

private:
    VkGraphicsPipelineCreateInfo createInfo = {};
    VkPipelineVertexInputStateCreateInfo vertexInputState = {};
    std::vector<VkVertexInputBindingDescription> vertexBindingDescriptions;
    std::vector<VkVertexInputAttributeDescription> vertexAttributeDescriptions;
    std::vector<VkViewport> viewports;
    std::vector<VkRect2D> scissors;
    std::vector<VkPipelineColorBlendAttachmentState> colorBlendAttachments;
    VkPipelineInputAssemblyStateCreateInfo inputAssembly = {};
};

} // Vulkan
