#include "SettingsScene.h"
#include "../Core/App.h"
#include "../GameState/GameStateManager.h"
#include "../Event/Input.h"

SettingsScene::SettingsScene(int width, int height) :
    Scene2D(width, height) {
}

SettingsScene::~SettingsScene() {
    Event::get()->keyPressed.disconnect<SettingsScene, &SettingsScene::onKeyPressed>(this);
}

void SettingsScene::init() {

}

void SettingsScene::draw(float dt) {

}

void SettingsScene::update(float dt) {

}

void SettingsScene::create() {

}

void SettingsScene::onKeyPressed(const SDL_KeyboardEvent& event) {
    if (event.keysym.sym == SDLK_ESCAPE) {
        GameStateManager::get()->popState();
        Input::get()->isKeyAccepted = true;
    }
}
