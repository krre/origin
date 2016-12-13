#include "SettingsState.h"

SettingsState::SettingsState() : GameState(SETTINGS), menuScene(300, 300) {
    isFreezable = true;
}

void SettingsState::init() {

}

void SettingsState::cleanup() {

}

void SettingsState::pause() {

}

void SettingsState::resume() {

}

void SettingsState::update(float dt) {
    menuScene.update(dt);
}

void SettingsState::draw(float dt) {
    menuScene.draw(dt);
}
