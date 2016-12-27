#include "MenuScene.h"
#include "../Core/App.h"
#include "../GameState/GameStateManager.h"
#include "../Event/Input.h"
#include "../Graphics/Vulkan/Manager.h"
#include "../Resource/ShaderResource.h"
#include "../Resource/ResourceManager.h"
#include "../Graphics/Vulkan/Command/CommandBuffer.h"

MenuScene::MenuScene(int width, int height) :
    Scene2D(width, height) {
}

MenuScene::~MenuScene() {
    delete commandBuffers;
    delete graphicsPipeline;
    delete pipelineLayout;
    delete descriptorSets;
    delete descriptorPool;
    delete descriptorSetLayout;
    delete uniformVert;
    delete uniformFrag;
    delete indexMemoryBuffer;
    delete vertexMemoryBuffer;
}

void MenuScene::init() {
    const std::vector<glm::vec2> vertices = {
        { -1.0f, -1.0f },
        {  1.0f, -1.0f },
        {  1.0f,  1.0f },
        { -1.0f,  1.0f },
    };

    const std::vector<uint16_t> indices = {
        0, 1, 2, 2, 3, 0
    };

    vertexMemoryBuffer = new Vulkan::MemoryBuffer(device, VK_BUFFER_USAGE_VERTEX_BUFFER_BIT, sizeof(vertices[0]) * vertices.size(), vertices.data());
    vertexMemoryBuffer->update();

    indexMemoryBuffer = new Vulkan::MemoryBuffer(device, VK_BUFFER_USAGE_INDEX_BUFFER_BIT, sizeof(indices[0]) * indices.size(), indices.data());
    indexMemoryBuffer->update();

    uniformVert = new Vulkan::Descriptor(device, VK_SHADER_STAGE_VERTEX_BIT, VK_BUFFER_USAGE_UNIFORM_BUFFER_BIT,
                                      VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER, 0, sizeof(uboVert), &uboVert);
    uniformVert->update();

    uniformFrag = new Vulkan::Descriptor(device, VK_SHADER_STAGE_FRAGMENT_BIT, VK_BUFFER_USAGE_UNIFORM_BUFFER_BIT,
                                      VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER, 1, sizeof(uboFrag), &uboFrag);
    uniformFrag->update();

    descriptorPool = new Vulkan::DescriptorPool(device);
    descriptorPool->addPoolSize(VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER, 2);
    descriptorPool->create();

    descriptorSetLayout = new Vulkan::DescriptorSetLayout(device);

    descriptorSetLayout->addLayoutBinding(*uniformVert->getLayoutBinding());
    descriptorSetLayout->addLayoutBinding(*uniformFrag->getLayoutBinding());
    descriptorSetLayout->create();

    descriptorSets = new Vulkan::DescriptorSets(device, descriptorPool);
    descriptorSets->addDescriptorSetLayout(descriptorSetLayout);
    descriptorSets->allocate();
    descriptorSets->addDescriptor(uniformVert);
    descriptorSets->addDescriptor(uniformFrag);
    descriptorSets->writeDescriptors();

    pipelineLayout = new Vulkan::PipelineLayout(device);
    pipelineLayout->addDescriptorSetLayout(descriptorSetLayout);
    pipelineLayout->create();

    graphicsPipeline = new Vulkan::GraphicsPipeline(device);

    ShaderResource* shaderResource = ResourceManager::get()->getResource<ShaderResource>("BaseVertShader");
    graphicsPipeline->addShaderCode(VK_SHADER_STAGE_VERTEX_BIT, "main", (size_t)shaderResource->getSize(), (uint32_t*)shaderResource->getData());

    shaderResource = ResourceManager::get()->getResource<ShaderResource>("BaseFragShader");
    graphicsPipeline->addShaderCode(VK_SHADER_STAGE_FRAGMENT_BIT, "main", (size_t)shaderResource->getSize(), (uint32_t*)shaderResource->getData());

    VkVertexInputBindingDescription bindingDescription = {};
    bindingDescription.binding = 0;
    bindingDescription.stride = sizeof(glm::vec2);
    bindingDescription.inputRate = VK_VERTEX_INPUT_RATE_VERTEX;
    graphicsPipeline->setVertexBindingDescriptions({ bindingDescription });

    VkVertexInputAttributeDescription attributeDescriptions = {};
    attributeDescriptions.binding = 0;
    attributeDescriptions.location = 0;
    attributeDescriptions.format = VK_FORMAT_R32G32_SFLOAT;
    attributeDescriptions.offset = 0;
    graphicsPipeline->setVertexAttributeDescriptions({ attributeDescriptions });

    graphicsPipeline->setExtent(Vulkan::Manager::get()->getSwapchain()->getExtent());
    graphicsPipeline->setPipelineLayout(pipelineLayout);
    graphicsPipeline->setRenderPass(Vulkan::Manager::get()->getRenderPass());
    graphicsPipeline->create();

    commandBuffers = new Vulkan::CommandBuffers(device, Vulkan::Manager::get()->getCommandPool());
    commandBuffers->allocate(Vulkan::Manager::get()->getSwapchain()->getImageCount());

    for (size_t i = 0; i < commandBuffers->getCount(); i++) {
        Vulkan::CommandBuffer commandBuffer(commandBuffers->at(i));
        commandBuffer.begin();

        VkClearValue clearColor = { 0.77, 0.83, 0.83, 1.0 };

        VkRenderPassBeginInfo renderPassInfo = {};
        renderPassInfo.sType = VK_STRUCTURE_TYPE_RENDER_PASS_BEGIN_INFO;
        renderPassInfo.renderPass = Vulkan::Manager::get()->getRenderPass()->getHandle();
        renderPassInfo.framebuffer = Vulkan::Manager::get()->getFramebuffer(i)->getHandle();
        renderPassInfo.renderArea.offset = { 0, 0 };
        renderPassInfo.renderArea.extent = Vulkan::Manager::get()->getSwapchain()->getExtent();
        renderPassInfo.clearValueCount = 1;
        renderPassInfo.pClearValues = &clearColor;

        vkCmdBeginRenderPass(commandBuffer.getHandle(), &renderPassInfo, VK_SUBPASS_CONTENTS_INLINE);

        vkCmdBindPipeline(commandBuffer.getHandle(), VK_PIPELINE_BIND_POINT_GRAPHICS, graphicsPipeline->getHandle());

        VkBuffer vertexBuffers[] = { vertexMemoryBuffer->getBuffer()->getHandle() };
        VkDeviceSize offsets[] = { 0 };
        vkCmdBindVertexBuffers(commandBuffer.getHandle(), 0, 1, vertexBuffers, offsets);
        vkCmdBindIndexBuffer(commandBuffer.getHandle(), indexMemoryBuffer->getBuffer()->getHandle(), 0, VK_INDEX_TYPE_UINT16);

        VkViewport viewport = {};
        viewport.width = Vulkan::Manager::get()->getSwapchain()->getExtent().width;
        viewport.height = Vulkan::Manager::get()->getSwapchain()->getExtent().height;
        vkCmdSetViewport(commandBuffer.getHandle(), 0, 1, &viewport);

        VkRect2D scissor = {};
        scissor.extent = Vulkan::Manager::get()->getSwapchain()->getExtent();
        vkCmdSetScissor(commandBuffer.getHandle(), 0, 1, &scissor);

        vkCmdBindDescriptorSets(commandBuffer.getHandle(), VK_PIPELINE_BIND_POINT_GRAPHICS, pipelineLayout->getHandle(), 0, descriptorSets->getCount(), descriptorSets->getData(), 0, nullptr);
        vkCmdDrawIndexed(commandBuffer.getHandle(), indices.size(), 1, 0, 0, 0);
        vkCmdEndRenderPass(commandBuffer.getHandle());

        commandBuffer.end();
    }

    Vulkan::Manager::get()->setCommandBuffers(commandBuffers);
}

void MenuScene::draw(float dt) {

}

void MenuScene::update(float dt) {

}

void MenuScene::create() {

}

void MenuScene::onKeyPressed(const SDL_KeyboardEvent& event) {
    if (event.keysym.sym == SDLK_ESCAPE) {
        GameStateManager::get()->popState();
        Input::get()->isKeyAccepted = true;
    }
}
