#include "GameScreen.h"
#include "UI/LinearLayout.h"
#include "UI/View3D.h"
#include "Scene/GameScene.h"

namespace Origin {

GameScreen::GameScreen() {
    View3D* gameView = new View3D();
    std::shared_ptr<GameScene> gameScene = std::make_shared<GameScene>();
    gameView->setScene(gameScene);
    LinearLayout* layout = new LinearLayout(LinearLayout::Direction::Vertical);
    layout->addControl(gameView);
    setLayout(layout);
}

} // Origin
