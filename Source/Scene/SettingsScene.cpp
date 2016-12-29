#include "SettingsScene.h"
#include "../Core/App.h"
#include "../Scene/SceneManager.h"
#include "../Event/Input.h"

SettingsScene::SettingsScene() {
}

SettingsScene::~SettingsScene() {

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
        SceneManager::get()->popScene();
        Input::get()->isKeyAccepted = true;
    }
}
