#include "MainMenuScene.h"
#include "../Core/App.h"
#include "../GameState/GameStateManager.h"
#include "../Event/Input.h"

MainMenuScene::MainMenuScene(int width, int height) :
    Scene2D(width, height) {
}

MainMenuScene::~MainMenuScene() {
    Event::get()->keyPressed.disconnect<MainMenuScene, &MainMenuScene::onKeyPressed>(this);
}

void MainMenuScene::draw(float dt) {

}


void MainMenuScene::onKeyPressed(const SDL_KeyboardEvent& event) {
    if (event.keysym.sym == SDLK_ESCAPE) {
        GameStateManager::get()->popState();
        Input::get()->isKeyAccepted = true;
    }
}
