#include "MenuScene.h"
#include "../Core/App.h"
#include "../GameState/GameStateManager.h"
#include "../Event/Input.h"

MenuScene::MenuScene(int width, int height) :
    Scene2D(width, height) {
}

MenuScene::~MenuScene() {
    Event::get()->keyPressed.disconnect<MenuScene, &MenuScene::onKeyPressed>(this);
}

void MenuScene::draw(float dt) {

}

void MenuScene::update(float dt) {

}

void MenuScene::onKeyPressed(const SDL_KeyboardEvent& event) {
    if (event.keysym.sym == SDLK_ESCAPE) {
        GameStateManager::get()->popState();
        Input::get()->isKeyAccepted = true;
    }
}
