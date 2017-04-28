#include "GraphicsPipeline.h"

using namespace Vulkan;

GraphicsPipeline::GraphicsPipeline(Device* device) :
        Pipeline(device) {
    createInfo.sType = VK_STRUCTURE_TYPE_GRAPHICS_PIPELINE_CREATE_INFO;
    createInfo.pVertexInputState = &vertexInputStateCreateInfo;
    createInfo.pInputAssemblyState = &inputAssemblyStateCreateInfo;
    createInfo.pRasterizationState = &rasterizationStateCreateInfo;
    createInfo.pMultisampleState = &multisampleStateCreateInfo;
    createInfo.pColorBlendState = &colorBlendStateCreateInfo;
    createInfo.pDepthStencilState = &depthStencilStateCreateInfo;

    vertexInputStateCreateInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_VERTEX_INPUT_STATE_CREATE_INFO;

    inputAssemblyStateCreateInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_INPUT_ASSEMBLY_STATE_CREATE_INFO;
    inputAssemblyStateCreateInfo.topology = VK_PRIMITIVE_TOPOLOGY_TRIANGLE_LIST;
    inputAssemblyStateCreateInfo.primitiveRestartEnable = VK_FALSE;

    rasterizationStateCreateInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_RASTERIZATION_STATE_CREATE_INFO;
    rasterizationStateCreateInfo.depthClampEnable = VK_FALSE;
    rasterizationStateCreateInfo.rasterizerDiscardEnable = VK_FALSE;
    rasterizationStateCreateInfo.polygonMode = VK_POLYGON_MODE_FILL;
    rasterizationStateCreateInfo.lineWidth = 1.0f;
    rasterizationStateCreateInfo.cullMode = VK_CULL_MODE_BACK_BIT;
    rasterizationStateCreateInfo.frontFace = VK_FRONT_FACE_CLOCKWISE;
    rasterizationStateCreateInfo.depthBiasEnable = VK_FALSE;

    multisampleStateCreateInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_MULTISAMPLE_STATE_CREATE_INFO;
    multisampleStateCreateInfo.sampleShadingEnable = VK_FALSE;
    multisampleStateCreateInfo.rasterizationSamples = VK_SAMPLE_COUNT_1_BIT;

    viewport.x = 0.0f;
    viewport.y = 0.0f;
    viewport.minDepth = 0.0f;
    viewport.maxDepth = 1.0f;

    scissor.offset = { 0, 0 };

    colorBlendAttachmentState.colorWriteMask = VK_COLOR_COMPONENT_R_BIT | VK_COLOR_COMPONENT_G_BIT | VK_COLOR_COMPONENT_B_BIT | VK_COLOR_COMPONENT_A_BIT;
    colorBlendAttachmentState.blendEnable = VK_FALSE;
    colorBlendAttachmentState.srcColorBlendFactor = VK_BLEND_FACTOR_ONE;
    colorBlendAttachmentState.dstColorBlendFactor = VK_BLEND_FACTOR_ONE_MINUS_SRC_ALPHA;
    colorBlendAttachmentState.colorBlendOp = VK_BLEND_OP_ADD;
    colorBlendAttachmentState.srcAlphaBlendFactor = VK_BLEND_FACTOR_ONE;
    colorBlendAttachmentState.dstAlphaBlendFactor = VK_BLEND_FACTOR_ZERO;
    colorBlendAttachmentState.alphaBlendOp = VK_BLEND_OP_ADD;

    colorBlendStateCreateInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_COLOR_BLEND_STATE_CREATE_INFO;
    colorBlendStateCreateInfo.logicOpEnable = VK_FALSE;
    colorBlendStateCreateInfo.logicOp = VK_LOGIC_OP_COPY;
    colorBlendStateCreateInfo.blendConstants[0] = 0.0f;
    colorBlendStateCreateInfo.blendConstants[1] = 0.0f;
    colorBlendStateCreateInfo.blendConstants[2] = 0.0f;
    colorBlendStateCreateInfo.blendConstants[3] = 0.0f;

    depthStencilStateCreateInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_DEPTH_STENCIL_STATE_CREATE_INFO;
    depthStencilStateCreateInfo.depthTestEnable = VK_TRUE;
    depthStencilStateCreateInfo.depthWriteEnable = VK_TRUE;
    depthStencilStateCreateInfo.depthCompareOp = VK_COMPARE_OP_LESS_OR_EQUAL;
    depthStencilStateCreateInfo.front = depthStencilStateCreateInfo.back;
    depthStencilStateCreateInfo.back.compareOp = VK_COMPARE_OP_ALWAYS;
}

void GraphicsPipeline::setExtent(VkExtent2D extent) {
    viewport.width = (float)extent.width;
    viewport.height = (float)extent.height;
    scissor.extent = extent;
}

void GraphicsPipeline::addVertexBindingDescription(VkVertexInputBindingDescription vertexBindingDescription) {
    vertexBindingDescriptions.push_back(vertexBindingDescription);
}

void GraphicsPipeline::addVertexAttributeDescription(VkVertexInputAttributeDescription vertexAttributeDescription) {
    vertexAttributeDescriptions.push_back(vertexAttributeDescription);
}

void GraphicsPipeline::addViewport(VkViewport viewport) {
    viewports.push_back(viewport);
}

void GraphicsPipeline::addScissor(VkRect2D scissor) {
    scissors.push_back(scissor);
}

void GraphicsPipeline::addColorBlendAttachment(VkPipelineColorBlendAttachmentState colorBlendAttachment) {
    colorBlendAttachmentStates.push_back(colorBlendAttachment);
}

void GraphicsPipeline::setPipelineLayout(VkPipelineLayout layout) {
    createInfo.layout = layout;
}

void GraphicsPipeline::setRenderPass(VkRenderPass renderPass) {
    createInfo.renderPass = renderPass;
}

void GraphicsPipeline::setBlendEnable(VkBool32 blendEnable) {
    colorBlendAttachmentState.blendEnable = blendEnable;
}

void GraphicsPipeline::create() {
    if (!viewports.size()) {
        viewports.push_back(viewport);
    }

    if (!scissors.size()) {
        scissors.push_back(scissor);
    }

    VkPipelineViewportStateCreateInfo viewportState = {};
    viewportState.sType = VK_STRUCTURE_TYPE_PIPELINE_VIEWPORT_STATE_CREATE_INFO;
    viewportState.viewportCount = viewports.size();
    viewportState.pViewports = viewports.data();
    viewportState.scissorCount = scissors.size();
    viewportState.pScissors = scissors.data();
    createInfo.pViewportState = &viewportState;

    if (colorBlendAttachmentStates.empty()) {
        colorBlendAttachmentStates.push_back(colorBlendAttachmentState);
    }

    colorBlendStateCreateInfo.attachmentCount = colorBlendAttachmentStates.size();
    colorBlendStateCreateInfo.pAttachments = colorBlendAttachmentStates.data();

    vertexInputStateCreateInfo.vertexBindingDescriptionCount = vertexBindingDescriptions.size();
    vertexInputStateCreateInfo.pVertexBindingDescriptions = vertexBindingDescriptions.data();

    vertexInputStateCreateInfo.vertexAttributeDescriptionCount = vertexAttributeDescriptions.size();
    vertexInputStateCreateInfo.pVertexAttributeDescriptions = vertexAttributeDescriptions.data();

    createInfo.stageCount = shaderStages.size();
    createInfo.pStages = shaderStages.data();

    VULKAN_CHECK_RESULT(vkCreateGraphicsPipelines(device->getHandle(), pipelineCache, 1, &createInfo, nullptr, &handle), "Failed to create graphics pipelines");
}
