#include "GraphicsPipeline.h"

using namespace Vulkan;

GraphicsPipeline::GraphicsPipeline(const Device* device) :  Pipeline(device) {
    createInfo.sType = VK_STRUCTURE_TYPE_GRAPHICS_PIPELINE_CREATE_INFO;
    vertexInputInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_VERTEX_INPUT_STATE_CREATE_INFO;
}

void GraphicsPipeline::setExtent(VkExtent2D extent) {
    this->extent = extent;
}

void GraphicsPipeline::setPipelineLayout(const PipelineLayout* pipelineLayout) {
    this->pipelineLayout = pipelineLayout;
}

void GraphicsPipeline::setRenderPass(const RenderPass* renderPass) {
    this->renderPass = renderPass;
}

void GraphicsPipeline::setVertexBindingDescriptions(const std::vector<VkVertexInputBindingDescription>& vertexBindingDescriptions) {
    this->vertexBindingDescriptions = vertexBindingDescriptions;
    vertexInputInfo.vertexBindingDescriptionCount = vertexBindingDescriptions.size();
    vertexInputInfo.pVertexBindingDescriptions = this->vertexBindingDescriptions.data();
}

void GraphicsPipeline::setVertexAttributeDescriptions(const std::vector<VkVertexInputAttributeDescription>& vertexAttributeDescriptions) {
    this->vertexAttributeDescriptions = vertexAttributeDescriptions;
    vertexInputInfo.vertexAttributeDescriptionCount = vertexAttributeDescriptions.size();
    vertexInputInfo.pVertexAttributeDescriptions = this->vertexAttributeDescriptions.data();
}

void GraphicsPipeline::setPipelineCache(PipelineCache* pipelineCache) {
    this->pipelineCache = pipelineCache;
}

VkResult GraphicsPipeline::create() {
    VkPipelineInputAssemblyStateCreateInfo inputAssembly = {};
    inputAssembly.sType = VK_STRUCTURE_TYPE_PIPELINE_INPUT_ASSEMBLY_STATE_CREATE_INFO;
    inputAssembly.topology = VK_PRIMITIVE_TOPOLOGY_TRIANGLE_LIST;
    inputAssembly.primitiveRestartEnable = VK_FALSE;

    VkViewport viewport = {};
    viewport.x = 0.0f;
    viewport.y = 0.0f;
    viewport.width = (float) extent.width;
    viewport.height = (float) extent.height;
    viewport.minDepth = 0.0f;
    viewport.maxDepth = 1.0f;

    VkRect2D scissor = {};
    scissor.offset = { 0, 0 };
    scissor.extent = extent;

    VkPipelineViewportStateCreateInfo viewportState = {};
    viewportState.sType = VK_STRUCTURE_TYPE_PIPELINE_VIEWPORT_STATE_CREATE_INFO;
    viewportState.viewportCount = 1;
    viewportState.pViewports = &viewport;
    viewportState.scissorCount = 1;
    viewportState.pScissors = &scissor;

    VkPipelineRasterizationStateCreateInfo rasterizer = {};
    rasterizer.sType = VK_STRUCTURE_TYPE_PIPELINE_RASTERIZATION_STATE_CREATE_INFO;
    rasterizer.depthClampEnable = VK_FALSE;
    rasterizer.rasterizerDiscardEnable = VK_FALSE;
    rasterizer.polygonMode = VK_POLYGON_MODE_FILL;
    rasterizer.lineWidth = 1.0f;
    rasterizer.cullMode = VK_CULL_MODE_BACK_BIT;
    rasterizer.frontFace = VK_FRONT_FACE_CLOCKWISE;
    rasterizer.depthBiasEnable = VK_FALSE;

    VkPipelineMultisampleStateCreateInfo multisampling = {};
    multisampling.sType = VK_STRUCTURE_TYPE_PIPELINE_MULTISAMPLE_STATE_CREATE_INFO;
    multisampling.sampleShadingEnable = VK_FALSE;
    multisampling.rasterizationSamples = VK_SAMPLE_COUNT_1_BIT;

    VkPipelineColorBlendAttachmentState colorBlendAttachment = {};
    colorBlendAttachment.colorWriteMask = VK_COLOR_COMPONENT_R_BIT | VK_COLOR_COMPONENT_G_BIT | VK_COLOR_COMPONENT_B_BIT | VK_COLOR_COMPONENT_A_BIT;
    colorBlendAttachment.blendEnable = VK_FALSE;

    VkPipelineColorBlendStateCreateInfo colorBlending = {};
    colorBlending.sType = VK_STRUCTURE_TYPE_PIPELINE_COLOR_BLEND_STATE_CREATE_INFO;
    colorBlending.logicOpEnable = VK_FALSE;
    colorBlending.logicOp = VK_LOGIC_OP_COPY;
    colorBlending.attachmentCount = 1;
    colorBlending.pAttachments = &colorBlendAttachment;
    colorBlending.blendConstants[0] = 0.0f;
    colorBlending.blendConstants[1] = 0.0f;
    colorBlending.blendConstants[2] = 0.0f;
    colorBlending.blendConstants[3] = 0.0f;

    createInfo.stageCount = shaderStages.size();
    createInfo.pStages = shaderStages.data();
    createInfo.pVertexInputState = &vertexInputInfo;
    createInfo.pInputAssemblyState = &inputAssembly;
    createInfo.pViewportState = &viewportState;
    createInfo.pRasterizationState = &rasterizer;
    createInfo.pMultisampleState = &multisampling;
    createInfo.pColorBlendState = &colorBlending;
    createInfo.layout = pipelineLayout->getHandle();
    createInfo.renderPass = renderPass->getHandle();
    createInfo.subpass = 0;
    createInfo.basePipelineHandle = VK_NULL_HANDLE;

    VkPipelineCache pc = pipelineCache != nullptr ? pipelineCache->getHandle() : VK_NULL_HANDLE;
    return checkError(vkCreateGraphicsPipelines(device->getHandle(), pc, 1, &createInfo, nullptr, &handle), "Failed to create graphics pipelines");
}
