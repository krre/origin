#include "GraphicsPipeline.h"

using namespace Vulkan;

GraphicsPipeline::GraphicsPipeline(const Device* device) :
        Pipeline(device) {
    createInfo.sType = VK_STRUCTURE_TYPE_GRAPHICS_PIPELINE_CREATE_INFO;
    createInfo.pVertexInputState = &vertexInputInfo;
    createInfo.pInputAssemblyState = &inputAssembly;
    createInfo.pRasterizationState = &rasterizer;
    createInfo.pMultisampleState = &multisampling;
    createInfo.pColorBlendState = &colorBlending;
    createInfo.pDepthStencilState = &depthStencilState;

    vertexInputInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_VERTEX_INPUT_STATE_CREATE_INFO;

    inputAssembly.sType = VK_STRUCTURE_TYPE_PIPELINE_INPUT_ASSEMBLY_STATE_CREATE_INFO;
    inputAssembly.topology = VK_PRIMITIVE_TOPOLOGY_TRIANGLE_LIST;
    inputAssembly.primitiveRestartEnable = VK_FALSE;

    rasterizer.sType = VK_STRUCTURE_TYPE_PIPELINE_RASTERIZATION_STATE_CREATE_INFO;
    rasterizer.depthClampEnable = VK_FALSE;
    rasterizer.rasterizerDiscardEnable = VK_FALSE;
    rasterizer.polygonMode = VK_POLYGON_MODE_FILL;
    rasterizer.lineWidth = 1.0f;
    rasterizer.cullMode = VK_CULL_MODE_BACK_BIT;
    rasterizer.frontFace = VK_FRONT_FACE_CLOCKWISE;
    rasterizer.depthBiasEnable = VK_FALSE;

    multisampling.sType = VK_STRUCTURE_TYPE_PIPELINE_MULTISAMPLE_STATE_CREATE_INFO;
    multisampling.sampleShadingEnable = VK_FALSE;
    multisampling.rasterizationSamples = VK_SAMPLE_COUNT_1_BIT;

    viewport.x = 0.0f;
    viewport.y = 0.0f;
    viewport.minDepth = 0.0f;
    viewport.maxDepth = 1.0f;

    scissor.offset = { 0, 0 };

    colorBlendAttachment.colorWriteMask = VK_COLOR_COMPONENT_R_BIT | VK_COLOR_COMPONENT_G_BIT | VK_COLOR_COMPONENT_B_BIT | VK_COLOR_COMPONENT_A_BIT;
    colorBlendAttachment.blendEnable = VK_FALSE;
    colorBlendAttachment.srcColorBlendFactor = VK_BLEND_FACTOR_ONE;
    colorBlendAttachment.dstColorBlendFactor = VK_BLEND_FACTOR_ONE;
    colorBlendAttachment.colorBlendOp = VK_BLEND_OP_ADD;
    colorBlendAttachment.srcAlphaBlendFactor = VK_BLEND_FACTOR_ONE;
    colorBlendAttachment.dstAlphaBlendFactor = VK_BLEND_FACTOR_ONE;
    colorBlendAttachment.alphaBlendOp = VK_BLEND_OP_ADD;

    colorBlending.sType = VK_STRUCTURE_TYPE_PIPELINE_COLOR_BLEND_STATE_CREATE_INFO;
    colorBlending.logicOpEnable = VK_FALSE;
    colorBlending.logicOp = VK_LOGIC_OP_COPY;
    colorBlending.blendConstants[0] = 0.0f;
    colorBlending.blendConstants[1] = 0.0f;
    colorBlending.blendConstants[2] = 0.0f;
    colorBlending.blendConstants[3] = 0.0f;

    depthStencilState.sType = VK_STRUCTURE_TYPE_PIPELINE_DEPTH_STENCIL_STATE_CREATE_INFO;
    depthStencilState.depthTestEnable = VK_TRUE;
    depthStencilState.depthWriteEnable = VK_TRUE;
    depthStencilState.depthCompareOp = VK_COMPARE_OP_LESS_OR_EQUAL;
    depthStencilState.front = depthStencilState.back;
    depthStencilState.back.compareOp = VK_COMPARE_OP_ALWAYS;
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
    colorBlendAttachments.push_back(colorBlendAttachment);
}

void GraphicsPipeline::setPipelineLayout(VkPipelineLayout layout) {
    createInfo.layout = layout;
}

void GraphicsPipeline::setRenderPass(VkRenderPass renderPass) {
    createInfo.renderPass = renderPass;
}

void GraphicsPipeline::setBlendEnable(VkBool32 blendEnable) {
    colorBlendAttachment.blendEnable = blendEnable;
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

    if (!colorBlendAttachments.size()) {
        colorBlendAttachments.push_back(colorBlendAttachment);
    }

    colorBlending.attachmentCount = colorBlendAttachments.size();
    colorBlending.pAttachments = colorBlendAttachments.data();

    vertexInputInfo.vertexBindingDescriptionCount = vertexBindingDescriptions.size();
    vertexInputInfo.pVertexBindingDescriptions = vertexBindingDescriptions.data();

    vertexInputInfo.vertexAttributeDescriptionCount = vertexAttributeDescriptions.size();
    vertexInputInfo.pVertexAttributeDescriptions = vertexAttributeDescriptions.data();

    createInfo.stageCount = shaderStages.size();
    createInfo.pStages = shaderStages.data();

    CHECK_RESULT(vkCreateGraphicsPipelines(device->getHandle(), pipelineCache, 1, &createInfo, nullptr, &handle), "Failed to create graphics pipelines");
}
