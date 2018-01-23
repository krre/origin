#include "MenuScene.h"
#include "Graphics/Plane.h"
#include "Event/Input.h"
#include "VulkanRenderer/ShaderProgram.h"
#include "VulkanRenderer/GpuBuffer.h"
#include "VulkanRenderer/API/Instance.h"
#include "VulkanRenderer/API/Surface/Swapchain.h"
#include "VulkanRenderer/API/Surface/Surface.h"
#include "VulkanRenderer/API/RenderPass.h"
#include "VulkanRenderer/API/Descriptor/DescriptorSets.h"
#include "VulkanRenderer/API/Pipeline/GraphicsPipeline.h"
#include "VulkanRenderer/API/Command/CommandBuffer.h"

namespace Origin {

MenuScene::MenuScene() {
    plane = std::make_unique<Plane>();
//    shaderProgram = std::make_unique<ShaderProgram>();
}

MenuScene::~MenuScene() {

}

void MenuScene::init() {
//    shaderProgram->addShader("Shader/Base.vert.spv");
//    shaderProgram->addShader("Shader/Base.frag.spv");

//    shaderProgram->bindUniform("uboVert", sizeof(uboVert), &uboVert);
//    shaderProgram->bindUniform("uboFrag", sizeof(uboFrag), &uboFrag);

//    shaderProgram->bindInput("position", sizeof(glm::vec2));

//    vertexBuffer->write(plane->getVertices().data(), plane->getVerticesSize());
//    indexBuffer->write(plane->getIndices().data(), plane->getIndicesSize());

//    shaderProgram->createPipeline();

//    buildCommandBuffers();

//    shaderProgram->writeUniform("uboVert");
//    shaderProgram->writeUniform("uboFrag");
}

void MenuScene::update(float dt) {

}

void MenuScene::create() {

}

//void MenuScene::writeCommands(Vulkan::CommandBuffer* commandBuffer) {
//    VkExtent2D extent = Vulkan::Instance::get()->getSurface()->getCurrentExtent();

//    VkViewport viewport = {};
//    viewport.width = extent.width;
//    viewport.height = extent.height;
//    viewport.maxDepth = 1.0;

//    VkRect2D scissor = {};
//    scissor.offset = { 0, 0 };
//    scissor.extent = extent;

//    const VkRenderPassBeginInfo* renderPassBeginInfo = Vulkan::Instance::get()->getSurface()->getSwapchain()->getRenderPass()->getBeginInfo();
//    commandBuffer->beginRenderPass(renderPassBeginInfo);

//    commandBuffer->bindPipeline(shaderProgram->getGraphicsPipeline());

//    commandBuffer->addViewport(viewport);
//    commandBuffer->setViewport(0);

//    commandBuffer->addScissor(scissor);
//    commandBuffer->setScissor(0);

//    commandBuffer->addVertexBuffer(vertexBuffer->getHandle());
//    commandBuffer->bindVertexBuffers();
//    commandBuffer->bindIndexBuffer(indexBuffer->getHandle(), indexBuffer->getIndexType());

//    for (int i = 0; i < shaderProgram->getDescriptorSets()->getCount(); i++) {
//        commandBuffer->addDescriptorSet(shaderProgram->getDescriptorSets()->at(i));
//    }

//    commandBuffer->bindDescriptorSets(shaderProgram->getGraphicsPipeline()->getBindPoint(), shaderProgram->getPipelineLayout()->getHandle());
//    commandBuffer->drawIndexed(plane->getIndices().size(), 1, 0, 0, 0);

//    commandBuffer->endRenderPass();
//}

void MenuScene::onKeyPressed(const SDL_KeyboardEvent& event) {
    if (event.keysym.sym == SDLK_ESCAPE) {
//        SceneManager::get()->popScene();
        Input::get()->isKeyAccepted = true;
    }
}

} // Origin
