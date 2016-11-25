#include "Pipeline.h"

using namespace Vulkan;

Pipeline::Pipeline(PipelineType type, const Device* device) :
    type(type),
    device(device) {
}

Pipeline::~Pipeline() {
    if (handle != VK_NULL_HANDLE) {
        vkDestroyPipeline(device->getHandle(), handle, nullptr);
    }
}

bool Pipeline::addShaderCode(ShaderType type, size_t size, const uint32_t* code) {
    std::shared_ptr<ShaderModule> shaderModule(new ShaderModule(device, size, code));
    if (!shaderModule->isValid()) {
        result = shaderModule->getResult();
        return false;
    }
    shaderModules[type] = shaderModule;
}

void Pipeline::create() {
    if (type == PipelineType::Graphics) {
        VkPipelineShaderStageCreateInfo vertShaderStageInfo = {};
        vertShaderStageInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO;
        vertShaderStageInfo.stage = VK_SHADER_STAGE_VERTEX_BIT;
        vertShaderStageInfo.module = shaderModules[ShaderType::Vertex]->getHandle();
        vertShaderStageInfo.pName = "main";

        VkPipelineShaderStageCreateInfo fragShaderStageInfo = {};
        fragShaderStageInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO;
        fragShaderStageInfo.stage = VK_SHADER_STAGE_FRAGMENT_BIT;
        fragShaderStageInfo.module = shaderModules[ShaderType::Fragment]->getHandle();
        fragShaderStageInfo.pName = "main";

        VkPipelineShaderStageCreateInfo shaderStages[] = {vertShaderStageInfo, fragShaderStageInfo};


        VkGraphicsPipelineCreateInfo createInfo = {};
        createInfo.sType = VK_STRUCTURE_TYPE_GRAPHICS_PIPELINE_CREATE_INFO;
        createInfo.stageCount = 2;
        createInfo.pStages = shaderStages;
//        createInfo.pVertexInputState = &vertexInputInfo;
//        createInfo.pInputAssemblyState = &inputAssembly;
//        createInfo.pViewportState = &viewportState;
//        createInfo.pRasterizationState = &rasterizer;
//        createInfo.pMultisampleState = &multisampling;
//        createInfo.pColorBlendState = &colorBlending;
//        createInfo.layout = pipelineLayout;
//        createInfo.renderPass = renderPass;
        createInfo.subpass = 0;
        createInfo.basePipelineHandle = VK_NULL_HANDLE;
        result = vkCreateGraphicsPipelines(device->getHandle(), VK_NULL_HANDLE, 1, &createInfo, nullptr, &handle);
    } else {
        VkComputePipelineCreateInfo createInfo = {};
        createInfo.sType = VK_STRUCTURE_TYPE_COMPUTE_PIPELINE_CREATE_INFO;
        result = vkCreateComputePipelines(device->getHandle(), VK_NULL_HANDLE, 1, &createInfo, nullptr, &handle);
    }
}
