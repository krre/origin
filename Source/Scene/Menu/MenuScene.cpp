#include "MenuScene.h"
#include "Core/App.h"
#include "Scene/SceneManager.h"
#include "Event/Input.h"
#include "Graphics/Buffer/VertexBuffer.h"
#include "Graphics/Buffer/IndexBuffer.h"
#include "Graphics/Vulkan/Instance.h"
#include "Graphics/Vulkan/Swapchain.h"
#include "Graphics/Vulkan/Framebuffer.h"
#include "Graphics/Vulkan/Descriptor/DescriptorSets.h"
#include "Graphics/Vulkan/Pipeline/GraphicsPipeline.h"
#include "Resource/ShaderResource.h"
#include "Resource/ResourceManager.h"
#include "Graphics/Vulkan/Command/CommandBuffer.h"
#include "Graphics/Vulkan/Command/CommandBuffers.h"
#include "Graphics/Plane.h"
#include "Graphics/Vulkan/Queue/SubmitQueue.h"

MenuScene::MenuScene() {
}

MenuScene::~MenuScene() {

}

void MenuScene::init() {
    shaderProgram.addShader("Shader/Base.vert.spv");
    shaderProgram.addShader("Shader/Base.frag.spv");

    shaderProgram.linkUniform("uboVert", sizeof(uboVert), &uboVert);
    shaderProgram.linkUniform("uboFrag", sizeof(uboFrag), &uboFrag);

    shaderProgram.linkInput("position", sizeof(glm::vec2));

    vertexBuffer->write(plane.getVertices().data(), plane.getVerticesSize());
    indexBuffer->write(plane.getIndices().data(), plane.getIndicesSize());

    shaderProgram.createPipeline();

    buildCommandBuffers();

    shaderProgram.writeUniform("uboVert");
    shaderProgram.writeUniform("uboFrag");
}

void MenuScene::update(float dt) {

}

void MenuScene::create() {

}

void MenuScene::writeCommands(Vulkan::CommandBuffer* commandBuffer) {
    VkExtent2D extent = Vulkan::Instance::get()->getSurface()->getCurrentExtent();

    VkViewport viewport = {};
    viewport.width = extent.width;
    viewport.height = extent.height;
    viewport.maxDepth = 1.0;

    VkRect2D scissor = {};
    scissor.offset = { 0, 0 };
    scissor.extent = extent;

    VkRenderPassBeginInfo* renderPassBeginInfo = &Vulkan::Instance::get()->getSurface()->getSwapchain()->getRenderPass()->beginInfo;
    commandBuffer->beginRenderPass(renderPassBeginInfo);

    commandBuffer->bindPipeline(shaderProgram.getGraphicsPipeline());

    commandBuffer->addViewport(viewport);
    commandBuffer->setViewport(0);

    commandBuffer->addScissor(scissor);
    commandBuffer->setScissor(0);

    commandBuffer->addVertexBuffer(vertexBuffer->getHandle());
    commandBuffer->bindVertexBuffers();
    commandBuffer->bindIndexBuffer(indexBuffer->getHandle());

    for (int i = 0; i < shaderProgram.getDescriptorSets()->getCount(); i++) {
        commandBuffer->addDescriptorSet(shaderProgram.getDescriptorSets()->at(i));
    }

    commandBuffer->bindDescriptorSets(shaderProgram.getGraphicsPipeline()->getBindPoint(), shaderProgram.getPipelineLayout()->getHandle());
    commandBuffer->drawIndexed(plane.getIndices().size(), 1, 0, 0, 0);

    commandBuffer->endRenderPass();
}

void MenuScene::onKeyPressed(const SDL_KeyboardEvent& event) {
    if (event.keysym.sym == SDLK_ESCAPE) {
        SceneManager::get()->popScene();
        Input::get()->isKeyAccepted = true;
    }
}
