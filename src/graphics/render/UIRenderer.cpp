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
    m_vertexBuffer = std::make_unique<Vulkan::GpuBuffer>(device, VK_BUFFER_USAGE_VERTEX_BUFFER_BIT, startSize);
    m_indirectBuffer = std::make_unique<Vulkan::GpuBuffer>(device, VK_BUFFER_USAGE_INDIRECT_BUFFER_BIT, sizeof(VkDrawIndirectCommand));
    m_uboBuffer = std::make_unique<Vulkan::GpuBuffer>(device, VK_BUFFER_USAGE_UNIFORM_BUFFER_BIT, sizeof(glm::mat4));

    m_sampler = std::make_unique<Vulkan::Sampler>(device);
    m_sampler->create();

    m_shaderProgram = std::make_unique<Vulkan::ShaderProgram>(device);
    m_shaderProgram->loadShader(ResourceManager::get()->dataPath() + "/shader/BaseShape.vert.spv");
    m_shaderProgram->loadShader(ResourceManager::get()->dataPath() + "/shader/BaseShape.frag.spv");

    VkDescriptorBufferInfo bufferInfo = {};
    bufferInfo.buffer = m_uboBuffer->handle();
    bufferInfo.range = VK_WHOLE_SIZE;
    m_shaderProgram->bindBuffer("ubo", bufferInfo);

    Font* font = ResourceManager::get()->load<Font>("fonts/inconsolatalgc.ttf");
    m_texture = font->texture();
    VkDescriptorImageInfo imageInfo = {};
    imageInfo.sampler = m_sampler->handle();
    imageInfo.imageView = m_texture->imageView()->handle();
    imageInfo.imageLayout = VK_IMAGE_LAYOUT_GENERAL;
    m_shaderProgram->bindImage("samplerImage", imageInfo);

    m_shaderProgram->create();

    m_graphicsPipeline = std::make_unique<Vulkan::GraphicsPipeline>(device);
    m_graphicsPipeline->setRenderPass(RenderManager::get()->renderPass()->handle());
    m_graphicsPipeline->setPipelineLayout(m_shaderProgram->pipelineLayout()->handle());

    m_graphicsPipeline->addDynamicState(VK_DYNAMIC_STATE_VIEWPORT);
    m_graphicsPipeline->addDynamicState(VK_DYNAMIC_STATE_SCISSOR);

    for (auto& shader : m_shaderProgram->shaders()) {
        m_graphicsPipeline->addShaderCode(shader->stage(), shader->code().size() * sizeof(uint32_t), shader->code().data(), "main");
    }

    VkVertexInputBindingDescription bindingDescription;
    bindingDescription.binding = 0;
    bindingDescription.stride = sizeof(UIBatch::Vertex);
    bindingDescription.inputRate = VK_VERTEX_INPUT_RATE_VERTEX;
    m_graphicsPipeline->addVertexBindingDescription(bindingDescription);

    {
        const Vulkan::Shader::LocationInfo locationInfo = m_shaderProgram->locationInfo("position");
        VkVertexInputAttributeDescription attributeDescription = {};
        attributeDescription.binding = bindingDescription.binding;
        attributeDescription.location = locationInfo.location;
        attributeDescription.format = locationInfo.format;
        m_graphicsPipeline->addVertexAttributeDescription(attributeDescription);
    }

    {
        const Vulkan::Shader::LocationInfo locationInfo = m_shaderProgram->locationInfo("uv");
        VkVertexInputAttributeDescription attributeDescription = {};
        attributeDescription.binding = bindingDescription.binding;
        attributeDescription.location = locationInfo.location;
        attributeDescription.format = locationInfo.format;
        attributeDescription.offset = sizeof(UIBatch::Vertex::pos);
        m_graphicsPipeline->addVertexAttributeDescription(attributeDescription);
    }

    {
        const Vulkan::Shader::LocationInfo locationInfo = m_shaderProgram->locationInfo("color");
        VkVertexInputAttributeDescription attributeDescription = {};
        attributeDescription.binding = bindingDescription.binding;
        attributeDescription.location = locationInfo.location;
        attributeDescription.format = locationInfo.format;
        attributeDescription.offset = sizeof(UIBatch::Vertex::pos) + sizeof(UIBatch::Vertex::uv);
        m_graphicsPipeline->addVertexAttributeDescription(attributeDescription);
    }

    m_graphicsPipeline->create();
}

UIRenderer::~UIRenderer() {

}

void UIRenderer::writeCommandBuffer(Vulkan::CommandBuffer* commandBuffer, Vulkan::Framebuffer* framebuffer) {
    glm::mat4 mvp = glm::ortho(0.0f, (float)framebuffer->width(), (float)framebuffer->height(), 0.0f);
    m_uboBuffer->write(&mvp, sizeof(mvp));

    commandBuffer->bindPipeline(m_graphicsPipeline.get());

    commandBuffer->clearVertexBuffers();
    commandBuffer->addVertexBuffer(m_vertexBuffer->handle());
    commandBuffer->bindVertexBuffers();

    if (m_shaderProgram->descriptorSets()->count()) {
        commandBuffer->clearDescriptorSets();
        for (int i = 0; i < m_shaderProgram->descriptorSets()->count(); i++) {
            commandBuffer->addDescriptorSet(m_shaderProgram->descriptorSets()->at(i));
        }
        commandBuffer->bindDescriptorSets(m_graphicsPipeline->bindPoint(), m_shaderProgram->pipelineLayout()->handle());
    }

    commandBuffer->drawIndirect(m_indirectBuffer->handle());
}

UIRenderer* UIRenderer::get() {
    return instance;
}

void UIRenderer::draw() {
    uint32_t vertextCount = m_vertices.size();
    uint32_t size = vertextCount * sizeof(UIBatch::Vertex);

    if (size > m_vertexBuffer->size()) {
        m_vertexBuffer = std::make_unique<Vulkan::GpuBuffer>(device(), VK_BUFFER_USAGE_VERTEX_BUFFER_BIT, size);
    }

    if (size) {
        m_vertexBuffer->write(m_vertices.data(), size);
        m_texture = m_batches.at(0).texture; // TODO: Sort batches and swith textures
    }

    VkDrawIndirectCommand indirectCommand = {};
    indirectCommand.vertexCount = vertextCount;
    indirectCommand.instanceCount = 1;
    m_indirectBuffer->write(&indirectCommand, sizeof(VkDrawIndirectCommand));
}

bool UIRenderer::active() const {
    return m_batches.size() > 0;
}

void UIRenderer::addBatch(UIBatch batch) {
    m_batches.push_back(batch);
}

void UIRenderer::clearBatches() {
    m_batches.clear();
    m_vertices.clear();
}
