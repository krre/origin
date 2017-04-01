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

    int binding = shaderProgram.createVertexInputBindingDescription(sizeof(Vertex));
    shaderProgram.linkInput("inPos", binding);
    shaderProgram.linkInput("inUV", binding, sizeof(Vertex::pos));

    Vulkan::GraphicsPipeline* graphicsPipeline = shaderProgram.getGraphicsPipeline();

    vertexBuffer = std::make_shared<Vulkan::Buffer>(device, VK_BUFFER_USAGE_VERTEX_BUFFER_BIT, MAX_CHAR_COUNT * sizeof(Font::Vertex), false);
    vertexBuffer->create();

    shaderProgram.createIndexBuffer(MAX_CHAR_COUNT * sizeof(uint32_t));

    pipelineCache.create();

    graphicsPipeline->setPipelineCache(pipelineCache.getHandle());
    graphicsPipeline->colorBlendAttachment.blendEnable = VK_TRUE;

    renderPass.setColorFormat(Vulkan::Manager::get()->getSurface()->getFormat(0).format);
    renderPass.setDepthFormat(device->getPhysicalDevice()->getSupportedDepthFormat());
    renderPass.setOverlayEnable(true);
    renderPass.create();

    shaderProgram.createPipeline();

    std::string text =
        "Origin " + std::string(VERSION_STRING) + "\n"
        "CPU count: " + std::to_string(SDL_GetCPUCount()) + "\n"
        "System RAM: " + std::to_string(SDL_GetSystemRAM()) + " MB";

    font->renderText(vertexBuffer.get(), shaderProgram.getIndexBuffer(), text);

    buildCommandBuffers();

    ubo.projection = glm::ortho(0.0f, (float)App::get()->getWidth(), 0.0f, (float)App::get()->getHeight());
    ubo.model = glm::scale(ubo.model, glm::vec3(scale, scale, scale));
    shaderProgram.writeUniform("ubo");

    create();
}

void DebugHUD::draw(float dt) {
    accumTime += dt;
    counter++;
    if (accumTime >= 0.5) {
        // Average fps for 0.5 sec (on resize may be > 60, so clamp to 60)
        int fpsNumber = std::min(int(std::round(counter / accumTime)), 60);
        fps.setText(std::to_string(fpsNumber) + " fps");
        accumTime = 0;
        counter = 0;
    }
//    Entity* character = EntityManager::get()->getEntity(Game::get()->getCharacterId()).get();
//    TransformComponent* tc = static_cast<TransformComponent*>(character->components[ComponentType::Transform].get());

//    posX.setText(std::string("Position X: ") + std::to_string(tc->position.x));
//    posY.setText(std::string("Position Y: ") + std::to_string(tc->position.y));
//    posZ.setText(std::string("Position Z: ") + std::to_string(tc->position.z));
//    Scene2D::draw(dt);
    queue->submit();
}

void DebugHUD::update(float dt) {

}

void DebugHUD::create() {
//    visible = false;

    version.resize(100, 10);
    version.setZ(1.0f);
    version.setText("Origin " + std::string(VERSION_STRING));

    vendor.resize(100, 10);
    vendor.setZ(1.0);
//    vendor.setText("Video driver: " + std::string(reinterpret_cast<const char*>(glGetString(GL_VENDOR))));

    vulkan.resize(100, 10);
    vulkan.setZ(1.0);
//    vulkan.setText("Vulkan " + std::string(reinterpret_cast<const char*>(glGetString(GL_VERSION))));

    cpuCount.resize(100, 10);
    cpuCount.setZ(1.0);
    cpuCount.setText("CPU count: " + std::to_string(SDL_GetCPUCount()));

    systemRAM.resize(100, 10);
    systemRAM.setZ(1.0);
    systemRAM.setText("System RAM: " + std::to_string(SDL_GetSystemRAM()) + " MB");

    fps.resize(100, 10);
    fps.setZ(1.0f);

    posX.resize(100, 10);
    posX.setZ(1.0f);

    posY.resize(100, 10);
    posY.setZ(1.0f);

    posZ.resize(100, 10);
    posZ.setZ(1.0f);

    statisticsLayout->setPosition(glm::vec2(5, 15));
    statisticsLayout->addControl(&version);
    statisticsLayout->addControl(&vendor);
    statisticsLayout->addControl(&vulkan);
    statisticsLayout->addControl(&cpuCount);
    statisticsLayout->addControl(&systemRAM);
    statisticsLayout->addControl(&fps);
    statisticsLayout->addControl(&posX);
    statisticsLayout->addControl(&posY);
    statisticsLayout->addControl(&posZ);
    setLayout(statisticsLayout);
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
    Vulkan::Manager::get()->getRenderPass()->setClearValue({ 0.0, 0.0, 0.0, 0.0 });
    VkRenderPassBeginInfo* renderPassBeginInfo = &Vulkan::Manager::get()->getRenderPass()->beginInfo;
    queue->clearCommandBuffers();

    for (size_t i = 0; i < commandBuffers.getCount(); i++) {
        renderPassBeginInfo->framebuffer = Vulkan::Manager::get()->getFramebuffer(i)->getHandle();

        Vulkan::CommandBuffer commandBuffer(commandBuffers.at(i));
        commandBuffer.begin();
        commandBuffer.beginRenderPass(renderPassBeginInfo);
        commandBuffer.bindPipeline(shaderProgram.getGraphicsPipeline());

        commandBuffer.addVertexBuffer(vertexBuffer->getHandle());
        commandBuffer.bindVertexBuffers();
        commandBuffer.bindIndexBuffer(shaderProgram.getIndexBuffer()->getHandle(), 0, VK_INDEX_TYPE_UINT32);

        for (int i = 0; i < shaderProgram.getDescriptorSets()->getCount(); i++) {
            commandBuffer.addDescriptorSet(shaderProgram.getDescriptorSets()->at(i));
        }
        commandBuffer.bindDescriptorSets(shaderProgram.getGraphicsPipeline()->getBindPoint(), shaderProgram.getPipelineLayout()->getHandle());

        commandBuffer.drawIndexed(font->getIndexCount(), 1, 0, 0, 0);

        commandBuffer.endRenderPass();
        commandBuffer.end();

        queue->addCommandBuffer(commandBuffer.getHandle());
    }
}
