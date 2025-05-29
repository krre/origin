#include "GameScreen.h"
#include "ui/View3D.h"
#include "ui/Overlay.h"
#include "ecs/scenes/GameScene.h"
#include "ui/dialog/PauseDialog.h"
#include "world/World.h"
#include <SDL_events.h>

GameScreen::GameScreen(const std::string& worldName) {
    World::load(worldName);

    auto gameView = new View3D(this);
    std::shared_ptr<GameScene> gameScene = std::make_shared<GameScene>();
    gameView->setScene(gameScene);
}

void GameScreen::keyPressed(const SDL_KeyboardEvent& event) {
    if (event.keysym.sym == SDLK_ESCAPE) {
        auto dialog = new PauseDialog;
        Overlay::get()->showDialog(dialog);
    }
}
