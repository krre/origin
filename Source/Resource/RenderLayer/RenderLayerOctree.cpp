#include "RenderLayerOctree.h"
#include "Vulkan/API/Framebuffer.h"
#include "Vulkan/API/Command/CommandBuffer.h"
#include "Vulkan/API/RenderPass.h"
#include "Vulkan/API/Descriptor/DescriptorSets.h"
#include "Vulkan/API/Pipeline/PipelineLayout.h"
#include "Graphics/Render/RenderManager.h"
#include "Vulkan/ShaderProgram.h"
#include "Vulkan/GpuBuffer.h"
#include "Vulkan/API/Pipeline/GraphicsPipeline.h"
#include "Resource/ResourceManager.h"
#include <glm/glm.hpp>

namespace Origin {

RenderLayerOctree::RenderLayerOctree(Vulkan::Device* device, Object* parent) : RenderLayer(device, parent) {
    std::vector<glm::vec2> plane = {
       { -1.0, 1.0 }, { -1.0, -1.0 }, { 1.0, -1.0 },
        { -1.0, 1.0 }, { 1.0, -1.0 }, { 1.0, 1.0 }
    };

    vertextCount = plane.size();

    int size = plane.size() * sizeof(glm::vec2);
    vertexBuffer = std::make_unique<Vulkan::GpuBuffer>(device, VK_BUFFER_USAGE_VERTEX_BUFFER_BIT, size);
    vertexBuffer->write(plane.data(), size);

    shaderProgram = std::make_unique<Vulkan::ShaderProgram>(device);
    shaderProgram->loadShader(ResourceManager::get()->getDataPath() + "/Shader/Octree.vert.spv");
    shaderProgram->loadShader(ResourceManager::get()->getDataPath() + "/Shader/Octree.frag.spv");

    uboBuffer = std::make_unique<Vulkan::GpuBuffer>(device, VK_BUFFER_USAGE_UNIFORM_BUFFER_BIT, sizeof(UBO));

    VkDescriptorBufferInfo bufferInfo = {};
    bufferInfo.buffer = uboBuffer->getHandle();
    bufferInfo.range = VK_WHOLE_SIZE;
    shaderProgram->bindBuffer("ubo", bufferInfo);

    blocksBuffer = std::make_unique<Vulkan::GpuBuffer>(device, VK_BUFFER_USAGE_UNIFORM_BUFFER_BIT, 1000000); // TODO: Use size from constant

    bufferInfo.buffer = blocksBuffer->getHandle();
    bufferInfo.range = VK_WHOLE_SIZE;
    shaderProgram->bindBuffer("blocks", bufferInfo);

    shaderProgram->create();

    graphicsPipeline = std::make_unique<Vulkan::GraphicsPipeline>(device);
    graphicsPipeline->setRenderPass(RenderManager::get()->getRenderPass()->getHandle());
    graphicsPipeline->setPipelineLayout(shaderProgram->getPipelineLayout()->getHandle());

    graphicsPipeline->addDynamicState(VK_DYNAMIC_STATE_VIEWPORT);
    graphicsPipeline->addDynamicState(VK_DYNAMIC_STATE_SCISSOR);

    for (auto& shader : shaderProgram->getShaders()) {
        graphicsPipeline->addShaderCode(shader->getStage(), shader->getCode().size() * sizeof(uint32_t), shader->getCode().data(), "main");
    }

    VkVertexInputBindingDescription bindingDescription;
    bindingDescription.binding = 0;
    bindingDescription.stride = sizeof(glm::vec2);
    bindingDescription.inputRate = VK_VERTEX_INPUT_RATE_VERTEX;
    graphicsPipeline->addVertexBindingDescription(bindingDescription);

    {
        const Vulkan::Shader::LocationInfo locationInfo = shaderProgram->getLocationInfo("position");
        VkVertexInputAttributeDescription attributeDescription = {};
        attributeDescription.binding = bindingDescription.binding;
        attributeDescription.location = locationInfo.location;
        attributeDescription.format = locationInfo.format;
        graphicsPipeline->addVertexAttributeDescription(attributeDescription);
    }

    graphicsPipeline->create();
}

RenderLayerOctree::~RenderLayerOctree() {

}

void RenderLayerOctree::write(Vulkan::CommandBuffer* commandBuffer, Vulkan::Framebuffer* framebuffer) {
    commandBuffer->bindPipeline(graphicsPipeline.get());

    commandBuffer->clearVertexBuffers();
    commandBuffer->addVertexBuffer(vertexBuffer->getHandle());
    commandBuffer->bindVertexBuffers();

    if (shaderProgram->getDescriptorSets()->getCount()) {
        commandBuffer->clearDescriptorSets();
        for (int i = 0; i < shaderProgram->getDescriptorSets()->getCount(); i++) {
            commandBuffer->addDescriptorSet(shaderProgram->getDescriptorSets()->at(i));
        }
        commandBuffer->bindDescriptorSets(graphicsPipeline->getBindPoint(), shaderProgram->getPipelineLayout()->getHandle());
    }

    commandBuffer->draw(vertextCount, 1, 0, 0);
}

void RenderLayerOctree::writeUBO(const UBO& ubo) {
    uboBuffer->write(&ubo, sizeof(UBO));
}

void RenderLayerOctree::writeBlocks(uint32_t offset, void* data, uint32_t size) {
    blocksBuffer->write(data, size, offset);
}

} // Origin
