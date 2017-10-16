#include "PauseScene.h"
#include "Core/Application.h"
#include "Graphics/Render/RenderWindow.h"
#include "Scene/SceneManager.h"
#include "Event/Input.h"
#include "UI/LinearLayout.h"
#include "UI/Button.h"
#include "Graphics/Vulkan/Wrapper/Surface/Swapchain.h"
#include "Graphics/Vulkan/Wrapper/Framebuffer.h"
#include "Graphics/Vulkan/Wrapper/Instance.h"
#include "Graphics/Vulkan/Wrapper/Command/CommandBuffer.h"
#include "Graphics/Vulkan/Wrapper/Command/CommandBuffers.h"
#include "Graphics/Vulkan/Wrapper/Queue/SubmitQueue.h"

PauseScene::PauseScene() {
    continueButton = std::make_unique<Button>();
    exitButton = std::make_unique<Button>();
}

PauseScene::~PauseScene() {

}

void PauseScene::init() {
    buildCommandBuffers();
    create();
}

void PauseScene::update(float dt) {
    layout->setPosition({ ((int)Application::get()->getWindow()->getWidth() - layout->getSize().width) / 2, ((int)Application::get()->getWindow()->getHeight() - layout->getSize().height) / 2 });
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
    Application::get()->quit();
}
