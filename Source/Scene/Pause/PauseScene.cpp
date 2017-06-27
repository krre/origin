#include "PauseScene.h"
#include "Core/App.h"
#include "Scene/SceneManager.h"
#include "Event/Input.h"
#include "UI/LinearLayout.h"
#include "UI/Button.h"
#include "Graphics/Vulkan/Swapchain.h"
#include "Graphics/Vulkan/Framebuffer.h"
#include "Graphics/Vulkan/Instance.h"
#include "Graphics/Vulkan/Command/CommandBuffer.h"
#include "Graphics/Vulkan/Command/CommandBuffers.h"
#include "Graphics/Vulkan/Queue/SubmitQueue.h"

PauseScene::PauseScene() {
    continueButton = std::unique_ptr<Button>();
    exitButton = std::unique_ptr<Button>();
    isFullScreen = false;
}

PauseScene::~PauseScene() {

}

void PauseScene::init() {
    buildCommandBuffers();
    create();
}

void PauseScene::update(float dt) {
    layout->setPosition({ (App::get()->getWidth() - layout->getSize().width) / 2, (App::get()->getHeight() - layout->getSize().height) / 2 });
    layout->update();
}

void PauseScene::create() {
    continueButton->setText("Continue");
    continueButton->setZ(0.5f);

    exitButton->setText("Exit");
    exitButton->setZ(0.5f);

    layout->setSize({ 100, 25 });
    layout->setSpacing(25); // TODO: Fix - abnormally!
    layout->addControl(continueButton.get());
    layout->addControl(exitButton.get());
    setRootControl(layout);

    continueButton->clicked.connect<PauseScene, &PauseScene::onContinueButtonClicked>(this);
    exitButton->clicked.connect<PauseScene, &PauseScene::onExitButtonClicked>(this);
}

void PauseScene::onKeyPressed(const SDL_KeyboardEvent& event) {
    if (event.keysym.sym == SDLK_ESCAPE) {
        SceneManager::get()->popScene();
        Input::get()->isKeyAccepted = true;
    }
}

void PauseScene::onContinueButtonClicked() {
    SceneManager::get()->popScene();
}

void PauseScene::onExitButtonClicked() {
    App::get()->quit();
}
