#include "GameScreen.h"
#include "UI/View3D.h"
#include "UI/Overlay.h"
#include "ECS/Scenes/GameScene.h"
#include "UI/Dialog/PauseDialog.h"
#include "World/World.h"
#include <SDL_events.h>

GameScreen::GameScreen(const std::string& worldName) {
    World::load(worldName);

    View3D* gameView = new View3D(this);
    std::shared_ptr<GameScene> gameScene = std::make_shared<GameScene>();
    gameView->setScene(gameScene);
}

void GameScreen::keyPressed(const SDL_KeyboardEvent& event) {
    if (event.keysym.sym == SDLK_ESCAPE) {
        PauseDialog* dialog = new PauseDialog;
        Overlay::get()->showDialog(dialog);
    }
}
