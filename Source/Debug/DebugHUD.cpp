#include "DebugHUD.h"
#include "../Core/App.h"
#include "../Core/Game.h"
#include "../ECS/EntityManager.h"
#include "../ECS/Components/TransformComponent.h"
#include "../Resource/ShaderResource.h"
#include "../Resource/ResourceManager.h"
#include "../Graphics/Vulkan/Manager.h"
#include "../Graphics/Vulkan/Command/CommandBuffer.h"
#include <glm/glm.hpp>
#include <Origin.h>

DebugHUD::DebugHUD() :
        pipelineCache(device),
        renderPass(device),
        sampler(device),
        shaderProgram(device) {
    visible = false;

    int apiVersionNumber = device->getPhysicalDevice()->getProperties().apiVersion;
    int major = (apiVersionNumber >> 22) & 0x3FF;
    int minor = (apiVersionNumber >> 12) & 0x3FF;
    int patch = apiVersionNumber & 0xFFF;
    vulkanApiVersion = std::to_string(major) + "." + std::to_string(minor) + "." + std::to_string(patch);
}

DebugHUD::~DebugHUD() {

}

void DebugHUD::init() {
    Scene::init();

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

    vertexBuffer = std::make_shared<Vulkan::Buffer>(device, VK_BUFFER_USAGE_VERTEX_BUFFER_BIT, MAX_CHAR_COUNT * sizeof(Font::Vertex), false);
    vertexBuffer->create();

    shaderProgram.createIndexBuffer(MAX_CHAR_COUNT * sizeof(uint32_t));

    pipelineCache.create();

    graphicsPipeline->setPipelineCache(pipelineCache.getHandle());
    graphicsPipeline->setBlendEnable(VK_TRUE);

    renderPass.setColorFormat(Vulkan::Manager::get()->getSurface()->getFormat(0).format);
    renderPass.setBlendEnable(true);
    renderPass.create();

    shaderProgram.createPipeline();

    buildCommandBuffers();

    ubo.projection = glm::ortho(0.0f, (float)App::get()->getWidth(), 0.0f, (float)App::get()->getHeight());
    ubo.model = glm::translate(ubo.model, glm::vec3(7, 5, 0));
    float scale = 0.5;
    ubo.model = glm::scale(ubo.model, glm::vec3(scale, scale, scale));
    shaderProgram.writeUniform("ubo");
}

void DebugHUD::draw(float dt) {
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
        "Video driver: " + device->getPhysicalDevice()->getProperties().deviceName + "\n"
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
    queue->submit();
}

void DebugHUD::update(float dt) {

}

void DebugHUD::trigger() {
    visible = !visible;
    if (visible) {
        resume();
    } else {
        pause();
    }
}

void DebugHUD::buildCommandBuffers() {
    VkExtent2D extent = Vulkan::Manager::get()->getSurface()->getCurrentExtent();
    renderPass.beginInfo.renderArea.extent = extent;

    VkViewport viewport = {};
    viewport.width = extent.width;
    viewport.height = extent.height;
    viewport.maxDepth = 1.0;

    VkRect2D scissor = {};
    scissor.offset = { 0, 0 };
    scissor.extent = extent;

    queue->clearCommandBuffers();
    commandBuffers.destroy();
    commandBuffers.allocate(Vulkan::Manager::get()->getSwapchain()->getCount());

    for (size_t i = 0; i < commandBuffers.getCount(); i++) {
        renderPass.beginInfo.framebuffer = Vulkan::Manager::get()->getSwapchain()->getFramebuffer(i)->getHandle();

        Vulkan::CommandBuffer commandBuffer(commandBuffers.at(i));
        commandBuffer.begin();
        commandBuffer.beginRenderPass(&renderPass.beginInfo);
        commandBuffer.bindPipeline(shaderProgram.getGraphicsPipeline());

        commandBuffer.addViewport(viewport);
        commandBuffer.setViewport(0);

        commandBuffer.addScissor(scissor);
        commandBuffer.setScissor(0);

        commandBuffer.addVertexBuffer(vertexBuffer->getHandle());
        commandBuffer.bindVertexBuffers();
        commandBuffer.bindIndexBuffer(shaderProgram.getIndexBuffer()->getHandle(), 0, VK_INDEX_TYPE_UINT32);

        for (int i = 0; i < shaderProgram.getDescriptorSets()->getCount(); i++) {
            commandBuffer.addDescriptorSet(shaderProgram.getDescriptorSets()->at(i));
        }
        commandBuffer.bindDescriptorSets(shaderProgram.getGraphicsPipeline()->getBindPoint(), shaderProgram.getPipelineLayout()->getHandle());

        commandBuffer.drawIndexed(MAX_CHAR_COUNT, 1, 0, 0, 0);

        commandBuffer.endRenderPass();
        commandBuffer.end();

        queue->addCommandBuffer(commandBuffer.getHandle());
    }
}
