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
    delete indexBuffer;
    delete vertexBuffer;
}

void MenuScene::init() {
    Scene::init();

    vertexBuffer = new Vulkan::Buffer(device, plane.getVerticesSize(), Vulkan::Buffer::Type::VERTEX, Vulkan::Buffer::Destination::DEVICE);
    vertexBuffer->create();

    Vulkan::Buffer vertexStageBuffer(device, plane.getVerticesSize(), Vulkan::Buffer::Type::TRANSFER_SRC);
    vertexStageBuffer.create();
    vertexStageBuffer.write(0, plane.getVerticesSize(), plane.getVertices().data());
    vertexStageBuffer.copy(vertexBuffer->getHandle(), plane.getVerticesSize());

    indexBuffer = new Vulkan::Buffer(device, plane.getIndicesSize(), Vulkan::Buffer::Type::INDEX, Vulkan::Buffer::Destination::DEVICE);
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
    Vulkan::Manager::get()->setCommandBuffers(commandBuffers);
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
    VkClearValue clearColor = { 0.77, 0.83, 0.83, 1.0 };

    VkRenderPassBeginInfo renderPassInfo = {};
    renderPassInfo.sType = VK_STRUCTURE_TYPE_RENDER_PASS_BEGIN_INFO;
    renderPassInfo.renderPass = Vulkan::Manager::get()->getRenderPass()->getHandle();
    renderPassInfo.renderArea.offset = { 0, 0 };
    renderPassInfo.renderArea.extent = Vulkan::Manager::get()->getSurface()->getCapabilities().currentExtent;
    renderPassInfo.clearValueCount = 1;
    renderPassInfo.pClearValues = &clearColor;

    for (size_t i = 0; i < commandBuffers->getCount(); i++) {
        renderPassInfo.framebuffer = Vulkan::Manager::get()->getFramebuffer(i)->getHandle();

        Vulkan::CommandBuffer commandBuffer(commandBuffers->at(i));
        commandBuffer.begin();
        commandBuffer.beginRenderPass(&renderPassInfo);
        commandBuffer.bindPipeline(&graphicsPipeline);

        commandBuffer.addVertexBuffer(vertexBuffer->getHandle());
        commandBuffer.bindVertexBuffers();

        vkCmdBindIndexBuffer(commandBuffer.getHandle(), indexBuffer->getHandle(), 0, VK_INDEX_TYPE_UINT16);

        VkViewport viewport = {};
        viewport.width = Vulkan::Manager::get()->getSurface()->getWidth();
        viewport.height = Vulkan::Manager::get()->getSurface()->getHeight();
        commandBuffer.addViewport(viewport);
        commandBuffer.setViewport(0);

        VkRect2D scissor = {};
        scissor.extent = Vulkan::Manager::get()->getSurface()->getCapabilities().currentExtent;
        vkCmdSetScissor(commandBuffer.getHandle(), 0, 1, &scissor);

        Vulkan::DescriptorSets* descriptorSets = &bsp.descriptorSets;
        vkCmdBindDescriptorSets(commandBuffer.getHandle(), VK_PIPELINE_BIND_POINT_GRAPHICS, pipelineLayout.getHandle(), 0, descriptorSets->getCount(), descriptorSets->getData(), 0, nullptr);
        vkCmdDrawIndexed(commandBuffer.getHandle(), plane.getIndices().size(), 1, 0, 0, 0);

        commandBuffer.endRenderPass();
        commandBuffer.end();
    }
}
