#include "MenuScene.h"
#include "../../Core/App.h"
#include "../../Scene/SceneManager.h"
#include "../../Event/Input.h"
#include "../../Graphics/Vulkan/Manager.h"
#include "../../Resource/ShaderResource.h"
#include "../../Resource/ResourceManager.h"
#include "../../Graphics/Vulkan/Command/CommandBuffer.h"
#include "../../Graphics/Plane.h"

MenuScene::MenuScene() :
    pipelineLayout(device),
    graphicsPipeline(device),
    bsp(device) {
}

MenuScene::~MenuScene() {

}

void MenuScene::init() {
    Scene::init();

    vertexBuffer = std::make_shared<Vulkan::Buffer>(device, plane.getVerticesSize(), Vulkan::Buffer::Type::VERTEX, Vulkan::Buffer::Destination::DEVICE);
    vertexBuffer->create();

    Vulkan::Buffer vertexStageBuffer(device, plane.getVerticesSize(), Vulkan::Buffer::Type::TRANSFER_SRC);
    vertexStageBuffer.create();
    vertexStageBuffer.write(0, plane.getVerticesSize(), plane.getVertices().data());
    vertexStageBuffer.copy(vertexBuffer->getHandle(), plane.getVerticesSize());

    indexBuffer = std::make_shared<Vulkan::Buffer>(device, plane.getIndicesSize(), Vulkan::Buffer::Type::INDEX, Vulkan::Buffer::Destination::DEVICE);
    indexBuffer->create();

    Vulkan::Buffer indexStageBuffer(device, plane.getIndicesSize(), Vulkan::Buffer::Type::TRANSFER_SRC);
    indexStageBuffer.create();
    indexStageBuffer.write(0, plane.getIndicesSize(), plane.getIndices().data());
    indexStageBuffer.copy(indexBuffer->getHandle(), plane.getIndicesSize());

    bsp.write("uboVert");
    bsp.write("uboFrag");

    pipelineLayout.addDescriptorSetLayout(&bsp.descriptorSetLayout);
    pipelineLayout.create();

    ShaderResource* shaderResource = bsp.shaderResources[ShaderProgram::Type::VERTEX];
    graphicsPipeline.addShaderCode(VK_SHADER_STAGE_VERTEX_BIT, shaderResource->getSize() * sizeof(uint32_t), shaderResource->getData());

    shaderResource = bsp.shaderResources[ShaderProgram::Type::FRAGMENT];
    graphicsPipeline.addShaderCode(VK_SHADER_STAGE_FRAGMENT_BIT, shaderResource->getSize() * sizeof(uint32_t), shaderResource->getData());

    VkVertexInputBindingDescription bindingDescription = {};
    bindingDescription.binding = 0;
    bindingDescription.stride = sizeof(glm::vec2);
    bindingDescription.inputRate = VK_VERTEX_INPUT_RATE_VERTEX;
    graphicsPipeline.addVertexBindingDescription(bindingDescription);

    VkVertexInputAttributeDescription attributeDescriptions = {};
    attributeDescriptions.binding = 0;
    attributeDescriptions.location = 0;
    attributeDescriptions.format = VK_FORMAT_R32G32_SFLOAT;
    attributeDescriptions.offset = 0;
    graphicsPipeline.addVertexAttributeDescription(attributeDescriptions);

    graphicsPipeline.setExtent(Vulkan::Manager::get()->getSurface()->getCapabilities().currentExtent);
    graphicsPipeline.createInfo.layout = pipelineLayout.getHandle();
    graphicsPipeline.createInfo.renderPass = Vulkan::Manager::get()->getRenderPass()->getHandle();
    graphicsPipeline.create();

    buildCommandBuffers();
}

void MenuScene::draw(float dt) {
    Vulkan::Manager::get()->setCommandBuffers(&commandBuffers);
    Vulkan::Manager::get()->submit();
}

void MenuScene::update(float dt) {

}

void MenuScene::create() {

}

void MenuScene::onKeyPressed(const SDL_KeyboardEvent& event) {
    if (event.keysym.sym == SDLK_ESCAPE) {
        SceneManager::get()->popScene();
        Input::get()->isKeyAccepted = true;
    }
}

void MenuScene::buildCommandBuffers() {
    Vulkan::Manager::get()->getRenderPass()->setClearValue({ 0.77, 0.83, 0.83, 1.0 });
    VkRenderPassBeginInfo* renderPassBeginInfo = &Vulkan::Manager::get()->getRenderPass()->beginInfo;
    queue->clearCommandBuffers();

    for (size_t i = 0; i < commandBuffers.getCount(); i++) {
        renderPassBeginInfo->framebuffer = Vulkan::Manager::get()->getFramebuffer(i)->getHandle();

        Vulkan::CommandBuffer commandBuffer(commandBuffers.at(i));
        commandBuffer.begin();
        commandBuffer.beginRenderPass(renderPassBeginInfo);
        commandBuffer.bindPipeline(&graphicsPipeline);

        commandBuffer.addVertexBuffer(vertexBuffer->getHandle());
        commandBuffer.bindVertexBuffers();
        commandBuffer.bindIndexBuffer(indexBuffer->getHandle(), VK_INDEX_TYPE_UINT16);

        Vulkan::DescriptorSets* descriptorSets = &bsp.descriptorSets;
        for (int i = 0; i < descriptorSets->getCount(); i++) {
            commandBuffer.addDescriptorSet(descriptorSets->at(i));
        }
        commandBuffer.bindDescriptorSets(&graphicsPipeline, pipelineLayout.getHandle());
        commandBuffer.drawIndexed(plane.getIndices().size(), 1, 0, 0, 0);

        commandBuffer.endRenderPass();
        commandBuffer.end();

        queue->addCommandBuffer(commandBuffer.getHandle());
    }
}
