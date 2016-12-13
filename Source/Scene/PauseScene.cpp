#include "PauseScene.h"
#include "../Core/App.h"
#include "../GameState/GameStateManager.h"
#include "../Event/Input.h"

PauseScene::PauseScene(int width, int height) :
    Scene2D(width, height) {

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

    Event::get()->keyPressed.connect<PauseScene, &PauseScene::onKeyPressed>(this);
    continueButton.clicked.connect<PauseScene, &PauseScene::onContinueButtonClicked>(this);
    exitButton.clicked.connect<PauseScene, &PauseScene::onExitButtonClicked>(this);
}

PauseScene::~PauseScene() {
    Event::get()->keyPressed.disconnect<PauseScene, &PauseScene::onKeyPressed>(this);
}

void PauseScene::draw(float dt) {
    layout->setPosition(glm::vec2((App::get()->getWidth() - layout->getWidth()) / 2.0, (App::get()->getHeight() - layout->getHeight()) / 2.0));
    layout->update();
    Scene2D::draw(dt);
}

void PauseScene::update(float dt) {

}

void PauseScene::onContinueButtonClicked() {
    GameStateManager::get()->popState();
}

void PauseScene::onExitButtonClicked() {
    App::get()->quit();
}

void PauseScene::onKeyPressed(const SDL_KeyboardEvent& event) {
    if (event.keysym.sym == SDLK_ESCAPE) {
        GameStateManager::get()->popState();
        Input::get()->isKeyAccepted = true;
    }
}
