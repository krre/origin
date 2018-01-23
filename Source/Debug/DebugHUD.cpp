#include "DebugHUD.h"
#include "Core/Application.h"
#include "Core/Game.h"
#include "Core/Defines.h"
#include "Scene/World/WorldScene.h"
#include "ECS/EntityManager.h"
#include "ECS/Entity.h"
#include "ECS/Components/TransformComponent.h"
#include "Resource/ResourceManager.h"
#include "VulkanRenderer/Texture.h"
#include "Graphics/Buffer/VertexBuffer.h"
#include "Graphics/Buffer/IndexBuffer.h"
#include "Graphics/Render/RenderEngine.h"
#include "VulkanRenderer/API/Instance.h"
#include "VulkanRenderer/API/Framebuffer.h"
#include "VulkanRenderer/API/Surface/Surface.h"
#include "VulkanRenderer/API/Descriptor/DescriptorSets.h"
#include "VulkanRenderer/API/Pipeline/GraphicsPipeline.h"
#include "VulkanRenderer/API/Command/CommandBuffer.h"
#include "VulkanRenderer/API/Command/CommandBuffers.h"
#include "VulkanRenderer/API/Queue.h"
#include "VulkanRenderer/API/Device/PhysicalDevice.h"
#include "Gui/Label.h"
#include "Gui/Font.h"
#include "Gui/Rectangle.h"
#include <glm/glm.hpp>

namespace Origin {

DebugHUD::DebugHUD() {
//    int apiVersionNumber = Vulkan::Instance::get()->getDefaultDevice()->getPhysicalDevice()->getProperties().apiVersion;
//    vulkanApiVersion = Vulkan::Instance::apiToString(apiVersionNumber);
}

DebugHUD::~DebugHUD() {

}

//void DebugHUD::init() {
//    std::shared_ptr<Rectangle> rect = std::make_shared<Rectangle>(Size(300, 200));
//    rect->setColor(Color(0.0, 0.0, 0.0, 0.5));
//    setRootControl(rect);

//    displayLabel = std::make_shared<Label>();
//    displayLabel->setPosition({ 7, 5 });
//    rect->addChild(displayLabel);

//    shaderProgram.addShader("Shader/SDF.vert.spv");
//    shaderProgram.addShader("Shader/SDF.frag.spv");

//    shaderProgram.bindUniform("ubo", sizeof(ubo), &ubo);

//    font = ResourceManager::get()->load<Font>("Fonts/inconsolata.fnt");

//    sampler.create();

//    VkDescriptorImageInfo descriptorImageInfo = {};
//    descriptorImageInfo.sampler = sampler.getHandle();
//    descriptorImageInfo.imageView = font->getTexture()->getImageView()->getHandle();
//    descriptorImageInfo.imageLayout = VK_IMAGE_LAYOUT_GENERAL;

//    shaderProgram.bindImage("samplerColor", descriptorImageInfo);

//    int binding = shaderProgram.createVertexInputBindingDescription(sizeof(Font::Vertex));
//    shaderProgram.bindInput("inPos", binding);
//    shaderProgram.bindInput("inUV", binding, sizeof(Font::Vertex::pos));

//    Vulkan::GraphicsPipeline* graphicsPipeline = shaderProgram.getGraphicsPipeline();

//    pipelineCache.create();

//    graphicsPipeline->setPipelineCache(pipelineCache.getHandle());
//    graphicsPipeline->setBlendEnable(VK_TRUE);

//    renderPass.setColorFormat(Vulkan::Instance::get()->getSurface()->getFormats().at(0).format);
//    renderPass.setBlendEnable(true);
//    renderPass.create();

//    setRenderPass(&renderPass);

//    shaderProgram.createPipeline();

//    buildCommandBuffers();

//    ubo.model = glm::translate(ubo.model, glm::vec3(7, 5, 0));
//    float scale = 0.5;
//    ubo.model = glm::scale(ubo.model, glm::vec3(scale, scale, scale));
//}

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
        std::string(APP_NAME) + " " + std::string(APP_VERSION_STR) + "\n" +
        std::to_string(fps) + " fps\n"
        "Video driver: " + RenderEngine::get()->getGraphicsDevice()->getPhysicalDevice()->getProperties().deviceName + "\n"
        "Vulkan API: " + vulkanApiVersion + "\n"
        "CPU count: " + std::to_string(SDL_GetCPUCount()) + "\n"
        "System RAM: " + std::to_string(SDL_GetSystemRAM()) + " MB";

//    if (Game::get()->getWorldScene()) {
//        Entity* character = EntityManager::get()->getEntity(Game::get()->getWorldScene()->getCharacterId()).get();
//        TransformComponent* tc = static_cast<TransformComponent*>(character->components[ComponentType::Transform].get());
//        std::string pos = "\n"
//        "Position X: " + std::to_string(tc->position.x) + "\n"
//        "Position Y: " + std::to_string(tc->position.y) + "\n"
//        "Position Z: " + std::to_string(tc->position.z);

//        text += pos;
//    }

//    font->renderText(vertexBuffer.get(), indexBuffer.get(), text);

    displayLabel->setText(text);
}

void DebugHUD::trigger() {
//    visible = !visible;
//    if (visible) {
//        resume();
//    } else {
//        pause();
//    }
}

//void DebugHUD::writeCommands(Vulkan::CommandBuffer* commandBuffer) {
//    VkExtent2D extent = Vulkan::Instance::get()->getSurface()->getCurrentExtent();

//    VkViewport viewport = {};
//    viewport.width = extent.width;
//    viewport.height = extent.height;
//    viewport.maxDepth = 1.0;

//    VkRect2D scissor = {};
//    scissor.offset = { 0, 0 };
//    scissor.extent = extent;

//    renderPass.setExtent(extent);
//    commandBuffer->beginRenderPass(renderPass.getBeginInfo());

//    commandBuffer->bindPipeline(shaderProgram.getGraphicsPipeline());

//    commandBuffer->addViewport(viewport);
//    commandBuffer->setViewport(0);

//    commandBuffer->addScissor(scissor);
//    commandBuffer->setScissor(0);

//    commandBuffer->addVertexBuffer(vertexBuffer->getHandle());
//    commandBuffer->bindVertexBuffers();
//    commandBuffer->bindIndexBuffer(indexBuffer->getHandle(), indexBuffer->getIndexType());

//    for (int i = 0; i < shaderProgram.getDescriptorSets()->getCount(); i++) {
//        commandBuffer->addDescriptorSet(shaderProgram.getDescriptorSets()->at(i));
//    }
//    commandBuffer->bindDescriptorSets(shaderProgram.getGraphicsPipeline()->getBindPoint(), shaderProgram.getPipelineLayout()->getHandle());
//    commandBuffer->drawIndexed(MAX_CHAR_COUNT, 1, 0, 0, 0);

//    commandBuffer->endRenderPass();
//}

//void DebugHUD::onWindowResize(int width, int height) {
//    ubo.projection = glm::ortho(0.0f, (float)width, 0.0f, (float)height);
//    shaderProgram.writeUniform("ubo");
//}

} // Origin
