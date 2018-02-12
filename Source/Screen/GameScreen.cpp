#include "GameScreen.h"
#include "UI/LinearLayout.h"
#include "UI/View3D.h"
#include "Core/Game.h"
#include "UI/Overlay.h"
#include "ECS/Scenes/GameScene.h"
#include "UI/Dialog/PauseDialog.h"
#include "World/World.h"
#include <SDL_events.h>

namespace Origin {

GameScreen::GameScreen(const std::string& worldName) {
    Game::getWorld()->load(worldName);

    View3D* gameView = new View3D();
    std::shared_ptr<GameScene> gameScene = std::make_shared<GameScene>();
    gameView->setScene(gameScene);
    LinearLayout* layout = new LinearLayout(LinearLayout::Direction::Vertical);
    layout->addControl(gameView);
    setLayout(layout);
}

void GameScreen::keyPressed(const SDL_KeyboardEvent& event) {
    if (event.keysym.sym == SDLK_ESCAPE) {
        PauseDialog* dialog = new PauseDialog;
        Game::getOverlay()->showDialog(dialog);
    }
}

} // Origin
