#include "SettingsState.h"

SettingsState::SettingsState() : GameState(SETTINGS), settingsScene(300, 300) {
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
    settingsScene.update(dt);
}

void SettingsState::draw(float dt) {
    settingsScene.draw(dt);
}
