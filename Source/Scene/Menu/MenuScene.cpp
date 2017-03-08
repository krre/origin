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
    descriptorPool(device),
    descriptorSetLayout(device),
    pipelineLayout(device),
    graphicsPipeline(device) {
}

MenuScene::~MenuScene() {
    delete descriptorSets;
    delete uniformVert;
    delete uniformFrag;
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

    VkDeviceSize size = sizeof(UBOvert);
    uniformVert = new Vulkan::Descriptor(device, VK_SHADER_STAGE_VERTEX_BIT, VK_BUFFER_USAGE_UNIFORM_BUFFER_BIT,
                                      VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER, 0, size);
    uniformVert->write(0, size, &uboVert);

    size = sizeof(UBOfrag);
    uniformFrag = new Vulkan::Descriptor(device, VK_SHADER_STAGE_FRAGMENT_BIT, VK_BUFFER_USAGE_UNIFORM_BUFFER_BIT,
                                      VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER, 1, size);
    uniformFrag->write(0, size, &uboFrag);

    descriptorPool.addPoolSize(VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER, 2);
    descriptorPool.create();

    descriptorSetLayout.addLayoutBinding(uniformVert->setLayoutBinding);
    descriptorSetLayout.addLayoutBinding(uniformFrag->setLayoutBinding);
    descriptorSetLayout.create();

    descriptorSets = new Vulkan::DescriptorSets(device, &descriptorPool);
    descriptorSets->addDescriptorSetLayout(&descriptorSetLayout);
    descriptorSets->allocate();
    descriptorSets->addDescriptor(uniformVert);
    descriptorSets->addDescriptor(uniformFrag);
    descriptorSets->writeDescriptors();

    pipelineLayout.addDescriptorSetLayout(&descriptorSetLayout);
    pipelineLayout.create();

    ShaderResource* shaderResource = ResourceManager::get()->load<ShaderResource>("Shader/Base.vert.spv");
    graphicsPipeline.addShaderCode(VK_SHADER_STAGE_VERTEX_BIT, shaderResource->getSize() * sizeof(uint32_t), shaderResource->getData());

    shaderResource = ResourceManager::get()->load<ShaderResource>("Shader/Base.frag.spv");;
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

        vkCmdBeginRenderPass(commandBuffer.getHandle(), &renderPassInfo, VK_SUBPASS_CONTENTS_INLINE);

        vkCmdBindPipeline(commandBuffer.getHandle(), VK_PIPELINE_BIND_POINT_GRAPHICS, graphicsPipeline.getHandle());

        VkBuffer vertexBuffers[] = { vertexBuffer->getHandle() };
        VkDeviceSize offsets[] = { 0 };
        vkCmdBindVertexBuffers(commandBuffer.getHandle(), 0, 1, vertexBuffers, offsets);
        vkCmdBindIndexBuffer(commandBuffer.getHandle(), indexBuffer->getHandle(), 0, VK_INDEX_TYPE_UINT16);

        VkViewport viewport = {};
        viewport.width = Vulkan::Manager::get()->getSurface()->getCapabilities().currentExtent.width;
        viewport.height = Vulkan::Manager::get()->getSurface()->getCapabilities().currentExtent.height;
        commandBuffer.addViewport(viewport);
        commandBuffer.setViewports(0);

        VkRect2D scissor = {};
        scissor.extent = Vulkan::Manager::get()->getSurface()->getCapabilities().currentExtent;
        vkCmdSetScissor(commandBuffer.getHandle(), 0, 1, &scissor);

        vkCmdBindDescriptorSets(commandBuffer.getHandle(), VK_PIPELINE_BIND_POINT_GRAPHICS, pipelineLayout.getHandle(), 0, descriptorSets->getCount(), descriptorSets->getData(), 0, nullptr);
        vkCmdDrawIndexed(commandBuffer.getHandle(), plane.getIndices().size(), 1, 0, 0, 0);
        vkCmdEndRenderPass(commandBuffer.getHandle());

        commandBuffer.end();
    }
}
