#include "RenderPassOctree.h"
#include "Graphics/Color.h"
#include "Base/Game.h"
#include "Base/Window.h"
#include "Vulkan/API/RenderPass.h"
#include "Vulkan/API/Framebuffer.h"
#include "Vulkan/API/Image/ImageView.h"
#include "Vulkan/API/Command/CommandBuffer.h"
#include "Vulkan/API/Surface/Surface.h"
#include "Vulkan/API/RenderPass.h"
#include "Vulkan/API/Descriptor/DescriptorSets.h"
#include "Vulkan/API/Pipeline/PipelineLayout.h"
#include "Graphics/Render/RenderManager.h"
#include "Vulkan/ShaderProgram.h"
#include "Vulkan/GpuBuffer.h"
#include "Vulkan/API/Pipeline/GraphicsPipeline.h"
#include "Resource/ResourceManager.h"
#include "ECS/Scenes/Scene.h"
#include "Octree/Octree.h"
#include "UI/Font.h"

namespace Origin {

RenderPassOctree::RenderPassOctree(Vulkan::Device* device, Object* parent) :
        RenderPassResource(device, parent) {
    std::vector<glm::vec2> plane = {
        { -1.0, 1.0 }, { 1.0, 1.0 }, { 1.0, -1.0 },
        { -1.0, 1.0 }, { 1.0, -1.0 }, { -1.0, -1.0 }
    };
    vertextCount = plane.size();

    vertexBuffer = std::make_unique<Vulkan::GpuBuffer>(device, VK_BUFFER_USAGE_VERTEX_BUFFER_BIT, plane.size() * sizeof(glm::vec2));

    shaderProgram = std::make_unique<Vulkan::ShaderProgram>(device);
    shaderProgram->loadShader(ResourceManager::get()->getDataPath() + "/Shader/Octree.vert.spv");
    shaderProgram->loadShader(ResourceManager::get()->getDataPath() + "/Shader/Octree.frag.spv");

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

RenderPassOctree::~RenderPassOctree() {

}

void RenderPassOctree::write(Vulkan::CommandBuffer* commandBuffer, Vulkan::Framebuffer* framebuffer) {
    const Color& color = Window::get()->getColor();

    Vulkan::RenderPassBegin renderPassBegin(RenderManager::get()->getRenderPass()->getHandle());
    renderPassBegin.setFrameBuffer(framebuffer->getHandle());
    renderPassBegin.setRenderArea({ 0, 0, framebuffer->getWidth(), framebuffer->getHeight() });
    renderPassBegin.addClearValue({ color.getRed(), color.getGreen(), color.getBlue(), color.getAlpha() });
    VkClearValue depthColor = {};
    depthColor.depthStencil.depth = 1.0f;
    depthColor.depthStencil.stencil = 0.0f;
    renderPassBegin.addClearValue(depthColor);

    commandBuffer->beginRenderPass(renderPassBegin.getInfo());

    if (vertextCount) {
        commandBuffer->bindPipeline(graphicsPipeline.get());

        commandBuffer->addVertexBuffer(vertexBuffer->getHandle());
        commandBuffer->bindVertexBuffers();

        for (int i = 0; i < shaderProgram->getDescriptorSets()->getCount(); i++) {
            commandBuffer->addDescriptorSet(shaderProgram->getDescriptorSets()->at(i));
        }
        commandBuffer->bindDescriptorSets(graphicsPipeline->getBindPoint(), shaderProgram->getPipelineLayout()->getHandle());

        commandBuffer->draw(vertextCount, 1, 0, 0);
    }

    commandBuffer->endRenderPass();
}

} // Origin
