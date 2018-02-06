#include "RenderPassUI.h"
#include "Graphics/Color.h"
#include "Core/Application.h"
#include "Core/Window.h"
#include "VulkanRenderer/API/RenderPass.h"
#include "VulkanRenderer/API/Framebuffer.h"
#include "VulkanRenderer/API/Sampler.h"
#include "VulkanRenderer/API/Image/ImageView.h"
#include "VulkanRenderer/API/Command/CommandBuffer.h"
#include "VulkanRenderer/API/Surface/Surface.h"
#include "VulkanRenderer/API/RenderPass.h"
#include "VulkanRenderer/API/Descriptor/DescriptorSets.h"
#include "VulkanRenderer/API/Pipeline/PipelineLayout.h"
#include "Graphics/Render/RenderEngine.h"
#include "VulkanRenderer/ShaderProgram.h"
#include "VulkanRenderer/GpuBuffer.h"
#include "VulkanRenderer/Texture.h"
#include "VulkanRenderer/API/Pipeline/GraphicsPipeline.h"
#include "Resource/ResourceManager.h"
#include "UI/UIBatch.h"
#include "UI/Font.h"
#include <glm/gtc/matrix_transform.hpp>

namespace Origin {

RenderPassUI::RenderPassUI(Vulkan::Device* device) : RenderPassResource(device) {
    renderPass = std::make_unique<Vulkan::RenderPass>(device);
    renderPass->setColorFormat(RenderEngine::get()->getSurface()->getFormats().at(0).format);
    renderPass->create();

    uint32_t startSize = 10000; // TODO: Set optimal value or take from constant
    vertexBuffer = std::make_unique<Vulkan::GpuBuffer>(VK_BUFFER_USAGE_VERTEX_BUFFER_BIT, startSize);

    uboBuffer = std::make_unique<Vulkan::GpuBuffer>(VK_BUFFER_USAGE_UNIFORM_BUFFER_BIT, sizeof(glm::mat4));

    sampler = std::make_unique<Vulkan::Sampler>(device);
    sampler->create();

    shaderProgram = std::make_unique<Vulkan::ShaderProgram>();
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
    graphicsPipeline->setBlendEnable(true);
    graphicsPipeline->setRenderPass(renderPass->getHandle());
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

RenderPassUI::~RenderPassUI() {

}

void RenderPassUI::write(Vulkan::CommandBuffer* commandBuffer, Vulkan::Framebuffer* framebuffer) {
    const Color& color = Application::get()->getWindow()->getColor();

    // TODO: Only need update on resize framebuffer
    glm::mat4 mvp = glm::ortho(0.0f, (float)framebuffer->getWidth(), (float)framebuffer->getHeight(), 0.0f);
    uboBuffer->write(&mvp, sizeof(mvp));

    Vulkan::RenderPassBegin renderPassBegin(renderPass->getHandle());
    renderPassBegin.setFrameBuffer(framebuffer->getHandle());
    renderPassBegin.setRenderArea({ 0, 0, framebuffer->getWidth(), framebuffer->getHeight() });
    renderPassBegin.addClearValue({ color.getRed(), color.getGreen(), color.getBlue(), color.getAlpha() });

    commandBuffer->beginRenderPass(renderPassBegin.getInfo());

    commandBuffer->bindPipeline(graphicsPipeline.get());

    commandBuffer->addVertexBuffer(vertexBuffer->getHandle());
    commandBuffer->bindVertexBuffers();

    for (int i = 0; i < shaderProgram->getDescriptorSets()->getCount(); i++) {
        commandBuffer->addDescriptorSet(shaderProgram->getDescriptorSets()->at(i));
    }
    commandBuffer->bindDescriptorSets(graphicsPipeline->getBindPoint(), shaderProgram->getPipelineLayout()->getHandle());

    commandBuffer->draw(vertextCount, 1, 0, 0);

    commandBuffer->endRenderPass();
}

void RenderPassUI::resizeVertexBuffer(uint32_t size) {
    vertexBuffer = std::make_unique<Vulkan::GpuBuffer>(VK_BUFFER_USAGE_VERTEX_BUFFER_BIT, size);
}

void RenderPassUI::setTexture(Vulkan::Texture* texture) {
    this->texture = texture;
}

} // Origin
