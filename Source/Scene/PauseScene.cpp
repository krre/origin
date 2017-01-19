#include "PauseScene.h"
#include "../Core/App.h"
#include "../Scene/SceneManager.h"
#include "../Event/Input.h"

PauseScene::PauseScene() {
    isFullScreen = false;
}

PauseScene::~PauseScene() {

}

void PauseScene::init() {

}

void PauseScene::draw(float dt) {
    layout->setPosition(glm::vec2((App::get()->getWidth() - layout->getWidth()) / 2.0, (App::get()->getHeight() - layout->getHeight()) / 2.0));
    layout->update();
    Scene2D::draw(dt);
}

void PauseScene::update(float dt) {

}

void PauseScene::create() {
    continueButton.setText("Continue");
    continueButton.setZ(0.5f);

    exitButton.setText("Exit");
    exitButton.setZ(0.5f);

    layout->setWidth(100);
    layout->setHeight(50);
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

}

void PauseScene::onContinueButtonClicked() {
    SceneManager::get()->popScene();
}

void PauseScene::onExitButtonClicked() {
    App::get()->quit();
}
