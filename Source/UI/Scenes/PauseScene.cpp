#include "PauseScene.h"

PauseScene::PauseScene(int width, int height) :
    Scene2D(width, height),
    continueRect(100, 100),
    exitRect(100, 20) {

    continueRect.setColor(glm::vec3(1.0, 1.0, 1.0));
    exitRect.setColor(glm::vec3(1.0, 1.0, 1.0));
    layout->addControl(&continueRect);
//    layout->addControl(&exitRect);
    setLayout(layout);
}
