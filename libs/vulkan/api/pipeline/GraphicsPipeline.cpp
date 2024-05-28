#include "GraphicsPipeline.h"

namespace Vulkan {

GraphicsPipeline::GraphicsPipeline(Device* device) :
        Pipeline(device) {
    createInfo.sType = VK_STRUCTURE_TYPE_GRAPHICS_PIPELINE_CREATE_INFO;
    createInfo.pVertexInputState = &vertexInputStateCreateInfo;
    createInfo.pInputAssemblyState = &inputAssemblyStateCreateInfo;
    createInfo.pRasterizationState = &rasterizationStateCreateInfo;
    createInfo.pMultisampleState = &multisampleStateCreateInfo;
    createInfo.pColorBlendState = &colorBlendStateCreateInfo;
    createInfo.pDepthStencilState = &depthStencilStateCreateInfo;
    createInfo.pViewportState = &viewportStateCreateInfo;
    createInfo.pDynamicState = &dynamicStateCreateInfo;
    createInfo.pTessellationState = &tessellationStateCreateInfo;

    vertexInputStateCreateInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_VERTEX_INPUT_STATE_CREATE_INFO;
    dynamicStateCreateInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_DYNAMIC_STATE_CREATE_INFO;
    viewportStateCreateInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_VIEWPORT_STATE_CREATE_INFO;

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
    depthStencilStateCreateInfo.back.compareOp = VK_COMPARE_OP_ALWAYS;
    depthStencilStateCreateInfo.front = depthStencilStateCreateInfo.back;
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

void GraphicsPipeline::addDynamicState(VkDynamicState dynamicState) {
    dynamicStates.push_back(dynamicState);
}

void GraphicsPipeline::setPrimitiveTopology(VkPrimitiveTopology topology) {
    inputAssemblyStateCreateInfo.topology = topology;
}

void GraphicsPipeline::addColorBlendAttachmentState(VkPipelineColorBlendAttachmentState colorBlendAttachmentState) {
    colorBlendAttachmentStates.push_back(colorBlendAttachmentState);
}

void GraphicsPipeline::setPipelineLayout(VkPipelineLayout layout) {
    createInfo.layout = layout;
}

void GraphicsPipeline::setRenderPass(VkRenderPass renderPass) {
    createInfo.renderPass = renderPass;
}

void GraphicsPipeline::create() {
    if (!viewports.size()) {
        addViewport({ 0, 0, 0, 0, 0}); // TODO: Dirty hack
    }

    if (!scissors.size()) {
        addScissor({ 0, 0, 0, 0 }); // TODO: Dirty hack
    }

    viewportStateCreateInfo.viewportCount = viewports.size();
    viewportStateCreateInfo.pViewports = viewports.data();
    viewportStateCreateInfo.scissorCount = scissors.size();
    viewportStateCreateInfo.pScissors = scissors.data();

    if (colorBlendAttachmentStates.empty()) {
        VkPipelineColorBlendAttachmentState colorBlendAttachmentState = {};
        colorBlendAttachmentState.colorWriteMask = VK_COLOR_COMPONENT_R_BIT | VK_COLOR_COMPONENT_G_BIT | VK_COLOR_COMPONENT_B_BIT | VK_COLOR_COMPONENT_A_BIT;
        colorBlendAttachmentState.blendEnable = VK_TRUE;
        colorBlendAttachmentState.srcColorBlendFactor = VK_BLEND_FACTOR_SRC_ALPHA;
        colorBlendAttachmentState.dstColorBlendFactor = VK_BLEND_FACTOR_ONE_MINUS_SRC_ALPHA;
        colorBlendAttachmentState.colorBlendOp = VK_BLEND_OP_ADD;
        colorBlendAttachmentState.srcAlphaBlendFactor = VK_BLEND_FACTOR_ONE_MINUS_SRC_ALPHA;
        colorBlendAttachmentState.dstAlphaBlendFactor = VK_BLEND_FACTOR_ONE;
        colorBlendAttachmentState.alphaBlendOp = VK_BLEND_OP_ADD;
        colorBlendAttachmentStates.push_back(colorBlendAttachmentState);
    }

    colorBlendStateCreateInfo.attachmentCount = colorBlendAttachmentStates.size();
    colorBlendStateCreateInfo.pAttachments = colorBlendAttachmentStates.data();

    vertexInputStateCreateInfo.vertexBindingDescriptionCount = vertexBindingDescriptions.size();
    vertexInputStateCreateInfo.pVertexBindingDescriptions = vertexBindingDescriptions.data();

    vertexInputStateCreateInfo.vertexAttributeDescriptionCount = vertexAttributeDescriptions.size();
    vertexInputStateCreateInfo.pVertexAttributeDescriptions = vertexAttributeDescriptions.data();

    dynamicStateCreateInfo.dynamicStateCount = dynamicStates.size();
    dynamicStateCreateInfo.pDynamicStates = dynamicStates.data();

    createInfo.stageCount = shaderStages.size();
    createInfo.pStages = shaderStages.data();

    VULKAN_CHECK_RESULT(vkCreateGraphicsPipelines(device->getHandle(), pipelineCache, 1, &createInfo, nullptr, &handle), "Failed to create graphics pipelines");
}

} // Vulkan
