#include "UIRenderer.h"
#include "graphics/render/RenderManager.h"
#include "vulkan/api/RenderPass.h"
#include "vulkan/api/Framebuffer.h"
#include "vulkan/api/Sampler.h"
#include "vulkan/api/image/ImageView.h"
#include "vulkan/api/command/CommandBuffer.h"
#include "vulkan/api/descriptor/DescriptorSets.h"
#include "vulkan/api/pipeline/PipelineLayout.h"
#include "vulkan/ShaderProgram.h"
#include "vulkan/GpuBuffer.h"
#include "vulkan/Texture.h"
#include "vulkan/api/pipeline/GraphicsPipeline.h"
#include "resource/ResourceManager.h"
#include "ui/UIBatch.h"
#include "ui/Font.h"
#include <glm/gtc/matrix_transform.hpp>

static UIRenderer* instance = nullptr;

UIRenderer::UIRenderer(Object* parent) : Renderer(parent) {
    instance = this;
    Vulkan::Device* device = Renderer::device();

    uint32_t startSize = 1000000; // TODO: Set optimal value or take from constant
    vertexBuffer = std::make_unique<Vulkan::GpuBuffer>(device, VK_BUFFER_USAGE_VERTEX_BUFFER_BIT, startSize);
    indirectBuffer = std::make_unique<Vulkan::GpuBuffer>(device, VK_BUFFER_USAGE_INDIRECT_BUFFER_BIT, sizeof(VkDrawIndirectCommand));
    uboBuffer = std::make_unique<Vulkan::GpuBuffer>(device, VK_BUFFER_USAGE_UNIFORM_BUFFER_BIT, sizeof(glm::mat4));

    sampler = std::make_unique<Vulkan::Sampler>(device);
    sampler->create();

    shaderProgram = std::make_unique<Vulkan::ShaderProgram>(device);
    shaderProgram->loadShader(ResourceManager::get()->dataPath() + "/shader/BaseShape.vert.spv");
    shaderProgram->loadShader(ResourceManager::get()->dataPath() + "/shader/BaseShape.frag.spv");

    VkDescriptorBufferInfo bufferInfo = {};
    bufferInfo.buffer = uboBuffer->handle();
    bufferInfo.range = VK_WHOLE_SIZE;
    shaderProgram->bindBuffer("ubo", bufferInfo);

    Font* font = ResourceManager::get()->load<Font>("fonts/inconsolatalgc.ttf");
    texture = font->texture();
    VkDescriptorImageInfo imageInfo = {};
    imageInfo.sampler = sampler->handle();
    imageInfo.imageView = texture->imageView()->handle();
    imageInfo.imageLayout = VK_IMAGE_LAYOUT_GENERAL;
    shaderProgram->bindImage("samplerImage", imageInfo);

    shaderProgram->create();

    graphicsPipeline = std::make_unique<Vulkan::GraphicsPipeline>(device);
    graphicsPipeline->setRenderPass(RenderManager::get()->renderPass()->handle());
    graphicsPipeline->setPipelineLayout(shaderProgram->pipelineLayout()->handle());

    graphicsPipeline->addDynamicState(VK_DYNAMIC_STATE_VIEWPORT);
    graphicsPipeline->addDynamicState(VK_DYNAMIC_STATE_SCISSOR);

    for (auto& shader : shaderProgram->shaders()) {
        graphicsPipeline->addShaderCode(shader->stage(), shader->code().size() * sizeof(uint32_t), shader->code().data(), "main");
    }

    VkVertexInputBindingDescription bindingDescription;
    bindingDescription.binding = 0;
    bindingDescription.stride = sizeof(UIBatch::Vertex);
    bindingDescription.inputRate = VK_VERTEX_INPUT_RATE_VERTEX;
    graphicsPipeline->addVertexBindingDescription(bindingDescription);

    {
        const Vulkan::Shader::LocationInfo locationInfo = shaderProgram->locationInfo("position");
        VkVertexInputAttributeDescription attributeDescription = {};
        attributeDescription.binding = bindingDescription.binding;
        attributeDescription.location = locationInfo.location;
        attributeDescription.format = locationInfo.format;
        graphicsPipeline->addVertexAttributeDescription(attributeDescription);
    }

    {
        const Vulkan::Shader::LocationInfo locationInfo = shaderProgram->locationInfo("uv");
        VkVertexInputAttributeDescription attributeDescription = {};
        attributeDescription.binding = bindingDescription.binding;
        attributeDescription.location = locationInfo.location;
        attributeDescription.format = locationInfo.format;
        attributeDescription.offset = sizeof(UIBatch::Vertex::pos);
        graphicsPipeline->addVertexAttributeDescription(attributeDescription);
    }

    {
        const Vulkan::Shader::LocationInfo locationInfo = shaderProgram->locationInfo("color");
        VkVertexInputAttributeDescription attributeDescription = {};
        attributeDescription.binding = bindingDescription.binding;
        attributeDescription.location = locationInfo.location;
        attributeDescription.format = locationInfo.format;
        attributeDescription.offset = sizeof(UIBatch::Vertex::pos) + sizeof(UIBatch::Vertex::uv);
        graphicsPipeline->addVertexAttributeDescription(attributeDescription);
    }

    graphicsPipeline->create();
}

UIRenderer::~UIRenderer() {

}

void UIRenderer::writeCommandBuffer(Vulkan::CommandBuffer* commandBuffer, Vulkan::Framebuffer* framebuffer) {
    glm::mat4 mvp = glm::ortho(0.0f, (float)framebuffer->width(), (float)framebuffer->height(), 0.0f);
    uboBuffer->write(&mvp, sizeof(mvp));

    commandBuffer->bindPipeline(graphicsPipeline.get());

    commandBuffer->clearVertexBuffers();
    commandBuffer->addVertexBuffer(vertexBuffer->handle());
    commandBuffer->bindVertexBuffers();

    if (shaderProgram->descriptorSets()->count()) {
        commandBuffer->clearDescriptorSets();
        for (int i = 0; i < shaderProgram->descriptorSets()->count(); i++) {
            commandBuffer->addDescriptorSet(shaderProgram->descriptorSets()->at(i));
        }
        commandBuffer->bindDescriptorSets(graphicsPipeline->bindPoint(), shaderProgram->pipelineLayout()->handle());
    }

    commandBuffer->drawIndirect(indirectBuffer->handle());
}

UIRenderer* UIRenderer::get() {
    return instance;
}

void UIRenderer::draw() {
    uint32_t vertextCount = m_vertices.size();
    uint32_t size = vertextCount * sizeof(UIBatch::Vertex);

    if (size > vertexBuffer->size()) {
        vertexBuffer = std::make_unique<Vulkan::GpuBuffer>(device(), VK_BUFFER_USAGE_VERTEX_BUFFER_BIT, size);
    }

    if (size) {
        vertexBuffer->write(m_vertices.data(), size);
        texture = batches.at(0).texture; // TODO: Sort batches and swith textures
    }

    VkDrawIndirectCommand indirectCommand = {};
    indirectCommand.vertexCount = vertextCount;
    indirectCommand.instanceCount = 1;
    indirectBuffer->write(&indirectCommand, sizeof(VkDrawIndirectCommand));
}

bool UIRenderer::active() const {
    return batches.size() > 0;
}

void UIRenderer::addBatch(UIBatch batch) {
    batches.push_back(batch);
}

void UIRenderer::clearBatches() {
    batches.clear();
    m_vertices.clear();
}
