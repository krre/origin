#include "GraphicsPipeline.h"

namespace Vulkan {

GraphicsPipeline::GraphicsPipeline(Device* device) :
        Pipeline(device) {
    m_createInfo.sType = VK_STRUCTURE_TYPE_GRAPHICS_PIPELINE_CREATE_INFO;
    m_createInfo.pVertexInputState = &m_vertexInputStateCreateInfo;
    m_createInfo.pInputAssemblyState = &m_inputAssemblyStateCreateInfo;
    m_createInfo.pRasterizationState = &m_rasterizationStateCreateInfo;
    m_createInfo.pMultisampleState = &m_multisampleStateCreateInfo;
    m_createInfo.pColorBlendState = &m_colorBlendStateCreateInfo;
    m_createInfo.pDepthStencilState = &m_depthStencilStateCreateInfo;
    m_createInfo.pViewportState = &m_viewportStateCreateInfo;
    m_createInfo.pDynamicState = &m_dynamicStateCreateInfo;
    m_createInfo.pTessellationState = &m_tessellationStateCreateInfo;

    m_vertexInputStateCreateInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_VERTEX_INPUT_STATE_CREATE_INFO;
    m_dynamicStateCreateInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_DYNAMIC_STATE_CREATE_INFO;
    m_viewportStateCreateInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_VIEWPORT_STATE_CREATE_INFO;

    m_inputAssemblyStateCreateInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_INPUT_ASSEMBLY_STATE_CREATE_INFO;
    m_inputAssemblyStateCreateInfo.topology = VK_PRIMITIVE_TOPOLOGY_TRIANGLE_LIST;
    m_inputAssemblyStateCreateInfo.primitiveRestartEnable = VK_FALSE;

    m_rasterizationStateCreateInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_RASTERIZATION_STATE_CREATE_INFO;
    m_rasterizationStateCreateInfo.depthClampEnable = VK_FALSE;
    m_rasterizationStateCreateInfo.rasterizerDiscardEnable = VK_FALSE;
    m_rasterizationStateCreateInfo.polygonMode = VK_POLYGON_MODE_FILL;
    m_rasterizationStateCreateInfo.lineWidth = 1.0f;
    m_rasterizationStateCreateInfo.cullMode = VK_CULL_MODE_BACK_BIT;
    m_rasterizationStateCreateInfo.frontFace = VK_FRONT_FACE_CLOCKWISE;
    m_rasterizationStateCreateInfo.depthBiasEnable = VK_FALSE;

    m_multisampleStateCreateInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_MULTISAMPLE_STATE_CREATE_INFO;
    m_multisampleStateCreateInfo.sampleShadingEnable = VK_FALSE;
    m_multisampleStateCreateInfo.rasterizationSamples = VK_SAMPLE_COUNT_1_BIT;

    m_colorBlendStateCreateInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_COLOR_BLEND_STATE_CREATE_INFO;
    m_colorBlendStateCreateInfo.logicOpEnable = VK_FALSE;
    m_colorBlendStateCreateInfo.logicOp = VK_LOGIC_OP_COPY;
    m_colorBlendStateCreateInfo.blendConstants[0] = 0.0f;
    m_colorBlendStateCreateInfo.blendConstants[1] = 0.0f;
    m_colorBlendStateCreateInfo.blendConstants[2] = 0.0f;
    m_colorBlendStateCreateInfo.blendConstants[3] = 0.0f;

    m_depthStencilStateCreateInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_DEPTH_STENCIL_STATE_CREATE_INFO;
    m_depthStencilStateCreateInfo.depthTestEnable = VK_TRUE;
    m_depthStencilStateCreateInfo.depthWriteEnable = VK_TRUE;
    m_depthStencilStateCreateInfo.depthCompareOp = VK_COMPARE_OP_LESS_OR_EQUAL;
    m_depthStencilStateCreateInfo.back.compareOp = VK_COMPARE_OP_ALWAYS;
    m_depthStencilStateCreateInfo.front = m_depthStencilStateCreateInfo.back;
}

void GraphicsPipeline::addVertexBindingDescription(VkVertexInputBindingDescription vertexBindingDescription) {
    m_vertexBindingDescriptions.push_back(vertexBindingDescription);
}

void GraphicsPipeline::addVertexAttributeDescription(VkVertexInputAttributeDescription vertexAttributeDescription) {
    m_vertexAttributeDescriptions.push_back(vertexAttributeDescription);
}

void GraphicsPipeline::addViewport(VkViewport viewport) {
    m_viewports.push_back(viewport);
}

void GraphicsPipeline::addScissor(VkRect2D scissor) {
    m_scissors.push_back(scissor);
}

void GraphicsPipeline::addDynamicState(VkDynamicState dynamicState) {
    m_dynamicStates.push_back(dynamicState);
}

void GraphicsPipeline::setPrimitiveTopology(VkPrimitiveTopology topology) {
    m_inputAssemblyStateCreateInfo.topology = topology;
}

void GraphicsPipeline::addColorBlendAttachmentState(VkPipelineColorBlendAttachmentState colorBlendAttachmentState) {
    m_colorBlendAttachmentStates.push_back(colorBlendAttachmentState);
}

void GraphicsPipeline::setPipelineLayout(VkPipelineLayout layout) {
    m_createInfo.layout = layout;
}

void GraphicsPipeline::setRenderPass(VkRenderPass renderPass) {
    m_createInfo.renderPass = renderPass;
}

void GraphicsPipeline::create() {
    if (!m_viewports.size()) {
        addViewport({ 0, 0, 0, 0, 0}); // TODO: Dirty hack
    }

    if (!m_scissors.size()) {
        addScissor({ 0, 0, 0, 0 }); // TODO: Dirty hack
    }

    m_viewportStateCreateInfo.viewportCount = m_viewports.size();
    m_viewportStateCreateInfo.pViewports = m_viewports.data();
    m_viewportStateCreateInfo.scissorCount = m_scissors.size();
    m_viewportStateCreateInfo.pScissors = m_scissors.data();

    if (m_colorBlendAttachmentStates.empty()) {
        VkPipelineColorBlendAttachmentState colorBlendAttachmentState = {};
        colorBlendAttachmentState.colorWriteMask = VK_COLOR_COMPONENT_R_BIT | VK_COLOR_COMPONENT_G_BIT | VK_COLOR_COMPONENT_B_BIT | VK_COLOR_COMPONENT_A_BIT;
        colorBlendAttachmentState.blendEnable = VK_TRUE;
        colorBlendAttachmentState.srcColorBlendFactor = VK_BLEND_FACTOR_SRC_ALPHA;
        colorBlendAttachmentState.dstColorBlendFactor = VK_BLEND_FACTOR_ONE_MINUS_SRC_ALPHA;
        colorBlendAttachmentState.colorBlendOp = VK_BLEND_OP_ADD;
        colorBlendAttachmentState.srcAlphaBlendFactor = VK_BLEND_FACTOR_ONE_MINUS_SRC_ALPHA;
        colorBlendAttachmentState.dstAlphaBlendFactor = VK_BLEND_FACTOR_ONE;
        colorBlendAttachmentState.alphaBlendOp = VK_BLEND_OP_ADD;
        m_colorBlendAttachmentStates.push_back(colorBlendAttachmentState);
    }

    m_colorBlendStateCreateInfo.attachmentCount = m_colorBlendAttachmentStates.size();
    m_colorBlendStateCreateInfo.pAttachments = m_colorBlendAttachmentStates.data();

    m_vertexInputStateCreateInfo.vertexBindingDescriptionCount = m_vertexBindingDescriptions.size();
    m_vertexInputStateCreateInfo.pVertexBindingDescriptions = m_vertexBindingDescriptions.data();

    m_vertexInputStateCreateInfo.vertexAttributeDescriptionCount = m_vertexAttributeDescriptions.size();
    m_vertexInputStateCreateInfo.pVertexAttributeDescriptions = m_vertexAttributeDescriptions.data();

    m_dynamicStateCreateInfo.dynamicStateCount = m_dynamicStates.size();
    m_dynamicStateCreateInfo.pDynamicStates = m_dynamicStates.data();

    m_createInfo.stageCount = m_shaderStages.size();
    m_createInfo.pStages = m_shaderStages.data();

    VULKAN_CHECK_RESULT(vkCreateGraphicsPipelines(m_device->handle(), m_pipelineCache, 1, &m_createInfo, nullptr, &m_handle), "Failed to create graphics pipelines");
}

}
