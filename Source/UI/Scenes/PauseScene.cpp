#include "PauseScene.h"
#include "../Core/App.h"

PauseScene::PauseScene(int width, int height) :
    Scene2D(width, height) {

    continueButton.setText("Continue");
    exitButton.setText("Exit");

    layout->setWidth(100);
    layout->setHeight(50);
    layout->setSpacing(25); // TODO: Fix - abnormally!
    layout->addControl(&continueButton);
    layout->addControl(&exitButton);
    setLayout(layout);
}

void PauseScene::draw(float dt) {
    layout->setPosition(glm::vec2((App::getInstance()->getWidth() - layout->getWidth()) / 2.0, (App::getInstance()->getHeight() - layout->getHeight()) / 2.0));
    layout->update();
    Scene2D::draw(dt);
}
