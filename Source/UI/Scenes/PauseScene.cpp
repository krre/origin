#include "PauseScene.h"

PauseScene::PauseScene(int width, int height) :
    Scene2D(width, height),
    continueRect(100, 20),
    exitRect(100, 20) {

    layout->addControl(&continueRect);
    layout->addControl(&exitRect);
    setLayout(layout);
}
