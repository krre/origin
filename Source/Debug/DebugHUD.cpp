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
    pipelineLayout(device),
    pipelineCache(device),
    graphicsPipeline(device),
    renderPass(device),
    tsp(device) {
    visible = false;
}

DebugHUD::~DebugHUD() {

}

void DebugHUD::init() {
    Scene::init();

    vertexBuffer = std::make_shared<Vulkan::Buffer>(device, VK_BUFFER_USAGE_VERTEX_BUFFER_BIT, MAX_CHAR_COUNT * sizeof(Font::Vertex), false);
    vertexBuffer->create();

    indexBuffer = std::make_shared<Vulkan::Buffer>(device, VK_BUFFER_USAGE_INDEX_BUFFER_BIT, MAX_CHAR_COUNT * sizeof(uint32_t), false);
    indexBuffer->create();

    pipelineLayout.addDescriptorSetLayout(&tsp.descriptorSetLayout);
    pipelineLayout.create();

    ShaderResource* shaderResource = tsp.shaderResources[ShaderProgram::Type::VERTEX];
    graphicsPipeline.addShaderCode(VK_SHADER_STAGE_VERTEX_BIT, shaderResource->getCodeSize() * sizeof(uint32_t), shaderResource->getCodeData());

    shaderResource = tsp.shaderResources[ShaderProgram::Type::FRAGMENT];
    graphicsPipeline.addShaderCode(VK_SHADER_STAGE_FRAGMENT_BIT, shaderResource->getCodeSize() * sizeof(uint32_t), shaderResource->getCodeData());

    VkVertexInputBindingDescription bindingDescriptionPos = {};
    bindingDescriptionPos.binding = 0;
    bindingDescriptionPos.stride = sizeof(glm::vec4);
    bindingDescriptionPos.inputRate = VK_VERTEX_INPUT_RATE_VERTEX;
    graphicsPipeline.addVertexBindingDescription(bindingDescriptionPos);

    VkVertexInputAttributeDescription attributeDescriptionPos = {};
    attributeDescriptionPos.binding = 0;
    attributeDescriptionPos.location = 0;
    attributeDescriptionPos.format = VK_FORMAT_R32G32_SFLOAT;
    attributeDescriptionPos.offset = 0;
    graphicsPipeline.addVertexAttributeDescription(attributeDescriptionPos);

    VkVertexInputBindingDescription bindingDescriptionUV = {};
    bindingDescriptionUV.binding = 1;
    bindingDescriptionUV.stride = sizeof(glm::vec4);
    bindingDescriptionUV.inputRate = VK_VERTEX_INPUT_RATE_VERTEX;
    graphicsPipeline.addVertexBindingDescription(bindingDescriptionUV);

    VkVertexInputAttributeDescription attributeDescriptionUV = {};
    attributeDescriptionUV.binding = 1;
    attributeDescriptionUV.location = 1;
    attributeDescriptionUV.format = VK_FORMAT_R32G32_SFLOAT;
    attributeDescriptionUV.offset = sizeof(glm::vec2);
    graphicsPipeline.addVertexAttributeDescription(attributeDescriptionUV);

    pipelineCache.create();

    graphicsPipeline.setExtent(Vulkan::Manager::get()->getSurface()->getCapabilities().currentExtent);
    graphicsPipeline.setPipelineCache(pipelineCache.getHandle());
    graphicsPipeline.createInfo.layout = pipelineLayout.getHandle();
    graphicsPipeline.createInfo.renderPass = Vulkan::Manager::get()->getRenderPass()->getHandle();
    graphicsPipeline.colorBlendAttachment.blendEnable = VK_TRUE;

    graphicsPipeline.create();

    renderPass.setColorFormat(Vulkan::Manager::get()->getSurface()->getFormat(0).format);
    renderPass.setDepthFormat(device->getPhysicalDevice()->getSupportedDepthFormat());
    renderPass.setOverlayEnable(true);
    renderPass.create();

    std::string test = "Origin";
    numLetters = tsp.getFont()->renderText(vertexBuffer.get(), indexBuffer.get(), test, 100, 100);

    buildCommandBuffers();

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
    Vulkan::Manager::get()->getRenderPass()->setClearValue({ 0.0, 0.0, 1.0, 0.0 });
    VkRenderPassBeginInfo* renderPassBeginInfo = &Vulkan::Manager::get()->getRenderPass()->beginInfo;
    queue->clearCommandBuffers();

    for (size_t i = 0; i < commandBuffers.getCount(); i++) {
        renderPassBeginInfo->framebuffer = Vulkan::Manager::get()->getFramebuffer(i)->getHandle();

        Vulkan::CommandBuffer commandBuffer(commandBuffers.at(i));
        commandBuffer.begin();
        commandBuffer.beginRenderPass(renderPassBeginInfo);
        commandBuffer.bindPipeline(&graphicsPipeline);

        commandBuffer.addVertexBuffer(vertexBuffer->getHandle());
        commandBuffer.addVertexBuffer(indexBuffer->getHandle()); // WRONG!!!
        commandBuffer.bindVertexBuffers();
        commandBuffer.bindIndexBuffer(indexBuffer->getHandle(), VK_INDEX_TYPE_UINT32);

        Vulkan::DescriptorSets* descriptorSets = &tsp.descriptorSets;
        for (int i = 0; i < descriptorSets->getCount(); i++) {
            commandBuffer.addDescriptorSet(descriptorSets->at(i));
        }
        commandBuffer.bindDescriptorSets(&graphicsPipeline, pipelineLayout.getHandle());
        commandBuffer.drawIndexed(tsp.getFont()->getIndexCount(), 1, 0, 0, 0);

        commandBuffer.endRenderPass();
        commandBuffer.end();

        queue->addCommandBuffer(commandBuffer.getHandle());
    }
}
