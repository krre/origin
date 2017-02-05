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
    sampler(device),
    descriptorPool(device),
    descriptorSetLayout(device),
    pipelineLayout(device),
    pipelineCache(device),
    graphicsPipeline(device),
    renderPass(device) {
    visible = false;
}

DebugHUD::~DebugHUD() {
    delete descriptorSets;
    delete samplerFont;
    delete samplerImage;
    delete samplerImageView;
    delete vertexBuffer;
}

void DebugHUD::init() {
    Scene::init();

    vertexBuffer = new Vulkan::Buffer(device, MAX_CHAR_COUNT * sizeof(glm::vec4), Vulkan::Buffer::Type::VERTEX, Vulkan::Buffer::Destination::HOST);
    vertexBuffer->create();

    sampler.create();

    samplerImage = new Vulkan::Image(device, 100, 100);
    samplerImage->setFormat(VK_FORMAT_R8_UNORM);
    samplerImage->setUsage(VK_IMAGE_USAGE_TRANSFER_DST_BIT | VK_IMAGE_USAGE_SAMPLED_BIT);
    samplerImage->create();

    samplerImageView = new Vulkan::ImageView(device, samplerImage->getHandle());
    samplerImageView->setFormat(VK_FORMAT_R8_UNORM);
    samplerImageView->create();

    samplerImage->setImageLayout(VK_IMAGE_LAYOUT_GENERAL);
    samplerImage->setSampler(&sampler);
    samplerImage->setImageView(samplerImageView);

    samplerFont = new Vulkan::Descriptor(device, VK_SHADER_STAGE_FRAGMENT_BIT, VK_BUFFER_USAGE_UNIFORM_BUFFER_BIT,
                                         VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER, 0, MAX_CHAR_COUNT * sizeof(glm::vec4));
    samplerFont->setImage(samplerImage);

    descriptorPool.addPoolSize(VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER, 1);
    descriptorPool.create();

    descriptorSetLayout.addLayoutBinding(*samplerFont->getLayoutBinding());
    descriptorSetLayout.create();

    pipelineLayout.addDescriptorSetLayout(&descriptorSetLayout);
    pipelineLayout.create();

    descriptorSets = new Vulkan::DescriptorSets(device, &descriptorPool);
    descriptorSets->addDescriptorSetLayout(&descriptorSetLayout);
    descriptorSets->allocate();
    descriptorSets->addDescriptor(samplerFont);
    descriptorSets->writeDescriptors();

    ShaderResource* shaderResource = ResourceManager::get()->getResource<ShaderResource>("TextVertShader");
    graphicsPipeline.addShaderCode(VK_SHADER_STAGE_VERTEX_BIT, (size_t)shaderResource->getSize(), (uint32_t*)shaderResource->getData());

    shaderResource = ResourceManager::get()->getResource<ShaderResource>("TextFragShader");
    graphicsPipeline.addShaderCode(VK_SHADER_STAGE_FRAGMENT_BIT, (size_t)shaderResource->getSize(), (uint32_t*)shaderResource->getData());

    VkVertexInputBindingDescription bindingDescriptionPos = {};
    bindingDescriptionPos.binding = 0;
    bindingDescriptionPos.stride = sizeof(glm::vec4);
    bindingDescriptionPos.inputRate = VK_VERTEX_INPUT_RATE_VERTEX;

    VkVertexInputBindingDescription bindingDescriptionUV = {};
    bindingDescriptionUV.binding = 1;
    bindingDescriptionUV.stride = sizeof(glm::vec4);
    bindingDescriptionUV.inputRate = VK_VERTEX_INPUT_RATE_VERTEX;


    graphicsPipeline.setVertexBindingDescriptions({ bindingDescriptionPos, bindingDescriptionUV });

    VkVertexInputAttributeDescription attributeDescriptionPos = {};
    attributeDescriptionPos.binding = 0;
    attributeDescriptionPos.location = 0;
    attributeDescriptionPos.format = VK_FORMAT_R32G32_SFLOAT;
    attributeDescriptionPos.offset = 0;

    VkVertexInputAttributeDescription attributeDescriptionUV = {};
    attributeDescriptionUV.binding = 0;
    attributeDescriptionUV.location = 1;
    attributeDescriptionUV.format = VK_FORMAT_R32G32_SFLOAT;
    attributeDescriptionUV.offset = sizeof(glm::vec2);

    graphicsPipeline.setVertexAttributeDescriptions({ attributeDescriptionPos, attributeDescriptionUV });

    pipelineCache.create();

    graphicsPipeline.setExtent(Vulkan::Manager::get()->getSwapchain()->getExtent());
    graphicsPipeline.setPipelineLayout(&pipelineLayout);
    graphicsPipeline.setPipelineCache(&pipelineCache);
    graphicsPipeline.setRenderPass(Vulkan::Manager::get()->getRenderPass());

    graphicsPipeline.create();

    renderPass.setFormat(Vulkan::Manager::get()->getSurface()->getFormat(0).format);
    renderPass.create();

    buildCommandBuffers();
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
    Vulkan::Manager::get()->setCommandBuffers(commandBuffers);
    Vulkan::Manager::get()->submit();
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
    VkClearValue clearColor = { 0.0, 0.0, 0.0, 0.0 };

    VkRenderPassBeginInfo renderPassInfo = {};
    renderPassInfo.sType = VK_STRUCTURE_TYPE_RENDER_PASS_BEGIN_INFO;
    renderPassInfo.renderPass = renderPass.getHandle();
    renderPassInfo.renderArea.offset = { 0, 0 };
    renderPassInfo.renderArea.extent = Vulkan::Manager::get()->getSwapchain()->getExtent();
    renderPassInfo.clearValueCount = 1;
    renderPassInfo.pClearValues = &clearColor;

    for (size_t i = 0; i < commandBuffers->getCount(); i++) {
        renderPassInfo.framebuffer = Vulkan::Manager::get()->getFramebuffer(i)->getHandle();

        Vulkan::CommandBuffer commandBuffer(commandBuffers->at(i));
        commandBuffer.begin();

        vkCmdBeginRenderPass(commandBuffer.getHandle(), &renderPassInfo, VK_SUBPASS_CONTENTS_INLINE);

        vkCmdBindPipeline(commandBuffer.getHandle(), VK_PIPELINE_BIND_POINT_GRAPHICS, graphicsPipeline.getHandle());

        VkViewport viewport = {};
        viewport.width = Vulkan::Manager::get()->getSwapchain()->getExtent().width;
        viewport.height = Vulkan::Manager::get()->getSwapchain()->getExtent().height;
        commandBuffer.addViewport(viewport);
        commandBuffer.setViewport(0);

        VkRect2D scissor = {};
        scissor.extent = Vulkan::Manager::get()->getSwapchain()->getExtent();
        vkCmdSetScissor(commandBuffer.getHandle(), 0, 1, &scissor);

        vkCmdBindDescriptorSets(commandBuffer.getHandle(), VK_PIPELINE_BIND_POINT_GRAPHICS, pipelineLayout.getHandle(), 0, descriptorSets->getCount(), descriptorSets->getData(), 0, nullptr);

        VkBuffer vertexBuffers[] = { vertexBuffer->getHandle() };
        VkDeviceSize offsets[] = { 0 };
        vkCmdBindVertexBuffers(commandBuffer.getHandle(), 0, 1, vertexBuffers, offsets);
        vkCmdBindVertexBuffers(commandBuffer.getHandle(), 1, 1, vertexBuffers, offsets);

        for (uint32_t j = 0; j < numLetters; j++) {
            vkCmdDraw(commandBuffer.getHandle(), 4, 1, j * 4, 0);
        }

        vkCmdEndRenderPass(commandBuffer.getHandle());

        commandBuffer.end();
    }
}
