#include "RenderLayerUI.h"
#include "Base/Window.h"
#include "Vulkan/API/RenderPass.h"
#include "Vulkan/API/Framebuffer.h"
#include "Vulkan/API/Sampler.h"
#include "Vulkan/API/Image/ImageView.h"
#include "Vulkan/API/Command/CommandBuffer.h"
#include "Vulkan/API/Surface/Surface.h"
#include "Vulkan/API/Descriptor/DescriptorSets.h"
#include "Vulkan/API/Pipeline/PipelineLayout.h"
#include "Graphics/Render/RenderManager.h"
#include "Vulkan/ShaderProgram.h"
#include "Vulkan/GpuBuffer.h"
#include "Vulkan/Texture.h"
#include "Vulkan/API/Pipeline/GraphicsPipeline.h"
#include "Resource/ResourceManager.h"
#include "UI/UIBatch.h"
#include "UI/Font.h"
#include <glm/gtc/matrix_transform.hpp>

namespace Origin {

RenderLayerUI::RenderLayerUI(Vulkan::Device* device, Object* parent) : RenderLayer(device, parent) {
    uint32_t startSize = 1000000; // TODO: Set optimal value or take from constant
    vertexBuffer = std::make_unique<Vulkan::GpuBuffer>(device, VK_BUFFER_USAGE_VERTEX_BUFFER_BIT, startSize);

    uboBuffer = std::make_unique<Vulkan::GpuBuffer>(device, VK_BUFFER_USAGE_UNIFORM_BUFFER_BIT, sizeof(glm::mat4));

    sampler = std::make_unique<Vulkan::Sampler>(device);
    sampler->create();

    shaderProgram = std::make_unique<Vulkan::ShaderProgram>(device);
    shaderProgram->loadShader(ResourceManager::get()->getDataPath() + "/Shader/BaseShape.vert.spv");
    shaderProgram->loadShader(ResourceManager::get()->getDataPath() + "/Shader/BaseShape.frag.spv");

    VkDescriptorBufferInfo bufferInfo = {};
    bufferInfo.buffer = uboBuffer->getHandle();
    bufferInfo.range = VK_WHOLE_SIZE;
    shaderProgram->bindBuffer("ubo", bufferInfo);

    Font* font = ResourceManager::get()->load<Font>("Fonts/inconsolatalgc.ttf");
    texture = font->getTexture();
    VkDescriptorImageInfo imageInfo = {};
    imageInfo.sampler = sampler->getHandle();
    imageInfo.imageView = texture->getImageView()->getHandle();
    imageInfo.imageLayout = VK_IMAGE_LAYOUT_GENERAL;
    shaderProgram->bindImage("samplerImage", imageInfo);

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
    bindingDescription.stride = sizeof(UIBatch::Vertex);
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

    {
        const Vulkan::Shader::LocationInfo locationInfo = shaderProgram->getLocationInfo("uv");
        VkVertexInputAttributeDescription attributeDescription = {};
        attributeDescription.binding = bindingDescription.binding;
        attributeDescription.location = locationInfo.location;
        attributeDescription.format = locationInfo.format;
        attributeDescription.offset = sizeof(UIBatch::Vertex::pos);
        graphicsPipeline->addVertexAttributeDescription(attributeDescription);
    }

    {
        const Vulkan::Shader::LocationInfo locationInfo = shaderProgram->getLocationInfo("color");
        VkVertexInputAttributeDescription attributeDescription = {};
        attributeDescription.binding = bindingDescription.binding;
        attributeDescription.location = locationInfo.location;
        attributeDescription.format = locationInfo.format;
        attributeDescription.offset = sizeof(UIBatch::Vertex::pos) + sizeof(UIBatch::Vertex::uv);
        graphicsPipeline->addVertexAttributeDescription(attributeDescription);
    }

    graphicsPipeline->create();
}

RenderLayerUI::~RenderLayerUI() {

}

void RenderLayerUI::write(Vulkan::CommandBuffer* commandBuffer, Vulkan::Framebuffer* framebuffer) {
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

} // Origin
