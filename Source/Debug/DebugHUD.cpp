#include "DebugHUD.h"
#include "Core/App.h"
#include "Core/Game.h"
#include "Scene/World/WorldScene.h"
#include "ECS/EntityManager.h"
#include "ECS/Components/TransformComponent.h"
#include "Resource/ShaderResource.h"
#include "Resource/ResourceManager.h"
#include "Graphics/Texture.h"
#include "Graphics/Buffer/VertexBuffer.h"
#include "Graphics/Buffer/IndexBuffer.h"
#include "Graphics/Vulkan/Instance.h"
#include "Graphics/Vulkan/Swapchain.h"
#include "Graphics/Vulkan/Framebuffer.h"
#include "Graphics/Vulkan/Descriptor/DescriptorSets.h"
#include "Graphics/Vulkan/Pipeline/GraphicsPipeline.h"
#include "Graphics/Vulkan/Command/CommandBuffer.h"
#include "Graphics/Vulkan/Command/CommandBuffers.h"
#include "Graphics/Vulkan/Queue/SubmitQueue.h"
#include "UI/Text/Label.h"
#include "UI/Rectangle.h"
#include <glm/glm.hpp>
#include <Origin.h>

DebugHUD::DebugHUD() {
    visible = false;
    setBackgroundColor(Color::TRANSPARENT);

    int apiVersionNumber = Vulkan::Instance::get()->getDefaultDevice()->getPhysicalDevice()->getProperties().apiVersion;
    vulkanApiVersion = Vulkan::Instance::apiToString(apiVersionNumber);
}

DebugHUD::~DebugHUD() {

}

void DebugHUD::init() {
    std::shared_ptr<Rectangle> rect = std::make_shared<Rectangle>(Size(300, 200));
    rect->setColor(Color(0.0, 0.0, 0.0, 0.5));
    setRoot(rect);

    displayLabel = std::make_shared<Label>();
    displayLabel->setPosition({ 7, 5 });
    rect->addControl(displayLabel);

    shaderProgram.addShader("Shader/SDF.vert.spv");
    shaderProgram.addShader("Shader/SDF.frag.spv");

    shaderProgram.linkUniform("ubo", sizeof(ubo), &ubo);

    font = ResourceManager::get()->load<Font>("Fonts/inconsolata.fnt");

    sampler.create();

    VkDescriptorImageInfo descriptorImageInfo = {};
    descriptorImageInfo.sampler = sampler.getHandle();
    descriptorImageInfo.imageView = font->getTexture()->getImageView()->getHandle();
    descriptorImageInfo.imageLayout = VK_IMAGE_LAYOUT_GENERAL;

    shaderProgram.linkImage("samplerColor", descriptorImageInfo);

    int binding = shaderProgram.createVertexInputBindingDescription(sizeof(Font::Vertex));
    shaderProgram.linkInput("inPos", binding);
    shaderProgram.linkInput("inUV", binding, sizeof(Font::Vertex::pos));

    Vulkan::GraphicsPipeline* graphicsPipeline = shaderProgram.getGraphicsPipeline();

    vertexBuffer = std::unique_ptr<VertexBuffer>(new VertexBuffer(MAX_CHAR_COUNT * sizeof(Font::Vertex)));
    indexBuffer = std::unique_ptr<IndexBuffer>(new IndexBuffer(MAX_CHAR_COUNT * sizeof(uint32_t)));

    pipelineCache.create();

    graphicsPipeline->setPipelineCache(pipelineCache.getHandle());
    graphicsPipeline->setBlendEnable(VK_TRUE);

    renderPass.setColorFormat(Vulkan::Instance::get()->getSurface()->getFormats().at(0).format);
    renderPass.setBlendEnable(true);
    renderPass.create();

    setRenderPass(&renderPass);

    shaderProgram.createPipeline();

    buildCommandBuffers();

    ubo.projection = glm::ortho(0.0f, (float)App::get()->getWidth(), 0.0f, (float)App::get()->getHeight());
    ubo.model = glm::translate(ubo.model, glm::vec3(7, 5, 0));
    float scale = 0.5;
    ubo.model = glm::scale(ubo.model, glm::vec3(scale, scale, scale));
    shaderProgram.writeUniform("ubo");
}

void DebugHUD::update(float dt) {
    accumTime += dt;
    counter++;
    if (accumTime >= 0.5) {
        // Average fps for 0.5 sec (on resize may be > 60, so clamp to 60)
        fps = int(std::round(counter / accumTime));
        accumTime = 0;
        counter = 0;
    }

    std::string text =
        "Origin " + std::string(VERSION_STRING) + "\n" +
        std::to_string(fps) + " fps\n"
        "Video driver: " + Vulkan::Instance::get()->getDefaultDevice()->getPhysicalDevice()->getProperties().deviceName + "\n"
        "Vulkan API: " + vulkanApiVersion + "\n"
        "CPU count: " + std::to_string(SDL_GetCPUCount()) + "\n"
        "System RAM: " + std::to_string(SDL_GetSystemRAM()) + " MB";

    if (Game::get()->getWorldScene()) {
        Entity* character = EntityManager::get()->getEntity(Game::get()->getWorldScene()->getCharacterId()).get();
        TransformComponent* tc = static_cast<TransformComponent*>(character->components[ComponentType::Transform].get());
        std::string pos = "\n"
        "Position X: " + std::to_string(tc->position.x) + "\n"
        "Position Y: " + std::to_string(tc->position.y) + "\n"
        "Position Z: " + std::to_string(tc->position.z);

        text += pos;
    }

    font->renderText(vertexBuffer.get(), shaderProgram.getIndexBuffer(), text);

    displayLabel->setText(text);
}

void DebugHUD::trigger() {
    visible = !visible;
    if (visible) {
        resume();
    } else {
        pause();
    }
}

void DebugHUD::writeCommands(Vulkan::CommandBuffer* commandBuffer) {
    VkExtent2D extent = Vulkan::Instance::get()->getSurface()->getCurrentExtent();

    VkViewport viewport = {};
    viewport.width = extent.width;
    viewport.height = extent.height;
    viewport.maxDepth = 1.0;

    VkRect2D scissor = {};
    scissor.offset = { 0, 0 };
    scissor.extent = extent;

    renderPass.beginInfo.renderArea.extent = extent;
    commandBuffer->beginRenderPass(&renderPass.beginInfo);

    commandBuffer->bindPipeline(shaderProgram.getGraphicsPipeline());

    commandBuffer->addViewport(viewport);
    commandBuffer->setViewport(0);

    commandBuffer->addScissor(scissor);
    commandBuffer->setScissor(0);

    commandBuffer->addVertexBuffer(vertexBuffer->getHandle());
    commandBuffer->bindVertexBuffers();
    commandBuffer->bindIndexBuffer(indexBuffer->getHandle(), 0, VK_INDEX_TYPE_UINT32);

    for (int i = 0; i < shaderProgram.getDescriptorSets()->getCount(); i++) {
        commandBuffer->addDescriptorSet(shaderProgram.getDescriptorSets()->at(i));
    }
    commandBuffer->bindDescriptorSets(shaderProgram.getGraphicsPipeline()->getBindPoint(), shaderProgram.getPipelineLayout()->getHandle());
    commandBuffer->drawIndexed(MAX_CHAR_COUNT, 1, 0, 0, 0);

    commandBuffer->endRenderPass();

    ubo.projection = glm::ortho(0.0f, (float)App::get()->getWidth(), 0.0f, (float)App::get()->getHeight());
    shaderProgram.writeUniform("ubo");
}
