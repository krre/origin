#include "PauseScene.h"
#include "../../Core/App.h"
#include "../../Scene/SceneManager.h"
#include "../../Event/Input.h"
#include "../../Graphics/Vulkan/Swapchain.h"
#include "../../Graphics/Vulkan/Command/CommandBuffer.h"

PauseScene::PauseScene() {
    isFullScreen = false;
}

PauseScene::~PauseScene() {

}

void PauseScene::init() {
    buildCommandBuffers();
    create();
}

void PauseScene::draw(float dt) {
    layout->setPosition(glm::vec2((App::get()->getWidth() - layout->getSize().x) / 2.0, (App::get()->getHeight() - layout->getSize().y) / 2.0));
    layout->update();
//    Scene2D::draw(dt);
    queue->submit();
}

void PauseScene::update(float dt) {

}

void PauseScene::create() {
    continueButton.setText("Continue");
    continueButton.setZ(0.5f);

    exitButton.setText("Exit");
    exitButton.setZ(0.5f);

    layout->setSize(100, 25);
    layout->setSpacing(25); // TODO: Fix - abnormally!
    layout->addControl(&continueButton);
    layout->addControl(&exitButton);
    setLayout(layout);

    continueButton.clicked.connect<PauseScene, &PauseScene::onContinueButtonClicked>(this);
    exitButton.clicked.connect<PauseScene, &PauseScene::onExitButtonClicked>(this);
}

void PauseScene::onKeyPressed(const SDL_KeyboardEvent& event) {
    if (event.keysym.sym == SDLK_ESCAPE) {
        SceneManager::get()->popScene();
        Input::get()->isKeyAccepted = true;
    }
}

void PauseScene::buildCommandBuffers() {
    Vulkan::Instance::get()->getSurface()->getSwapchain()->getRenderPass()->setClearValue({ 1.0, 0.0, 0.0, 1.0 });
    VkRenderPassBeginInfo* renderPassBeginInfo = &Vulkan::Instance::get()->getSurface()->getSwapchain()->getRenderPass()->beginInfo;
    queue->clearCommandBuffers();

    for (size_t i = 0; i < commandBuffers.getCount(); i++) {
        renderPassBeginInfo->framebuffer = Vulkan::Instance::get()->getSurface()->getSwapchain()->getFramebuffer(i)->getHandle();

        Vulkan::CommandBuffer commandBuffer(commandBuffers.at(i));
        commandBuffer.begin();
        commandBuffer.beginRenderPass(renderPassBeginInfo);


        commandBuffer.endRenderPass();
        commandBuffer.end();

        queue->addCommandBuffer(commandBuffer.getHandle());
    }
}

void PauseScene::onContinueButtonClicked() {
    SceneManager::get()->popScene();
}

void PauseScene::onExitButtonClicked() {
    App::get()->quit();
}
