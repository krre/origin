#include "MenuScene.h"
#include "Graphics/Plane.h"
#include "Scene/SceneManager.h"
#include "Event/Input.h"
#include "Graphics/ShaderProgram.h"
#include "Graphics/Buffer/VertexBuffer.h"
#include "Graphics/Buffer/IndexBuffer.h"
#include "Graphics/Render/Vulkan/Wrapper/Instance.h"
#include "Graphics/Render/Vulkan/Wrapper/Swapchain.h"
#include "Graphics/Render/Vulkan/Wrapper/Surface.h"
#include "Graphics/Render/Vulkan/Wrapper/RenderPass.h"
#include "Graphics/Render/Vulkan/Wrapper/Descriptor/DescriptorSets.h"
#include "Graphics/Render/Vulkan/Wrapper/Pipeline/GraphicsPipeline.h"
#include "Graphics/Render/Vulkan/Wrapper/Command/CommandBuffer.h"

MenuScene::MenuScene() {
    plane = std::make_unique<Plane>();
    shaderProgram = std::make_unique<ShaderProgram>();
}

MenuScene::~MenuScene() {

}

void MenuScene::init() {
    shaderProgram->addShader("Shader/Base.vert.spv");
    shaderProgram->addShader("Shader/Base.frag.spv");

    shaderProgram->bindUniform("uboVert", sizeof(uboVert), &uboVert);
    shaderProgram->bindUniform("uboFrag", sizeof(uboFrag), &uboFrag);

    shaderProgram->bindInput("position", sizeof(glm::vec2));

    vertexBuffer->write(plane->getVertices().data(), plane->getVerticesSize());
    indexBuffer->write(plane->getIndices().data(), plane->getIndicesSize());

    shaderProgram->createPipeline();

    buildCommandBuffers();

    shaderProgram->writeUniform("uboVert");
    shaderProgram->writeUniform("uboFrag");
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

    const VkRenderPassBeginInfo* renderPassBeginInfo = Vulkan::Instance::get()->getSurface()->getSwapchain()->getRenderPass()->getBeginInfo();
    commandBuffer->beginRenderPass(renderPassBeginInfo);

    commandBuffer->bindPipeline(shaderProgram->getGraphicsPipeline());

    commandBuffer->addViewport(viewport);
    commandBuffer->setViewport(0);

    commandBuffer->addScissor(scissor);
    commandBuffer->setScissor(0);

    commandBuffer->addVertexBuffer(vertexBuffer->getHandle());
    commandBuffer->bindVertexBuffers();
    commandBuffer->bindIndexBuffer(indexBuffer->getHandle(), indexBuffer->getIndexType());

    for (int i = 0; i < shaderProgram->getDescriptorSets()->getCount(); i++) {
        commandBuffer->addDescriptorSet(shaderProgram->getDescriptorSets()->at(i));
    }

    commandBuffer->bindDescriptorSets(shaderProgram->getGraphicsPipeline()->getBindPoint(), shaderProgram->getPipelineLayout()->getHandle());
    commandBuffer->drawIndexed(plane->getIndices().size(), 1, 0, 0, 0);

    commandBuffer->endRenderPass();
}

void MenuScene::onKeyPressed(const SDL_KeyboardEvent& event) {
    if (event.keysym.sym == SDLK_ESCAPE) {
        SceneManager::get()->popScene();
        Input::get()->isKeyAccepted = true;
    }
}
