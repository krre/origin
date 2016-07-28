#include "PauseScene.h"
#include "../Core/App.h"

PauseScene::PauseScene(int width, int height) :
    Scene2D(width, height),
    continueRect(100, 20),
    exitRect(100, 20) {

    layout->setWidth(100);
    layout->setHeight(50);
    layout->setSpacing(25); // TODO: Fix - abnormally!

    continueRect.setColor(glm::vec3(1.0, 1.0, 1.0));
    exitRect.setColor(glm::vec3(1.0, 1.0, 1.0));
    layout->addControl(&continueRect);
    layout->addControl(&exitRect);
    setLayout(layout);
}

void PauseScene::draw(float dt) {
    layout->setPosition(glm::vec2((App::getInstance()->getWidth() - layout->getWidth()) / 2.0, (App::getInstance()->getHeight() - layout->getHeight()) / 2.0));
    layout->update();
    Scene2D::draw(dt);
}
