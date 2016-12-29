#include "SettingsState.h"

SettingsState::SettingsState() : GameState(SETTINGS) {
    isFreezable = true;
}

void SettingsState::init() {
    settingsScene.init();
    settingsScene.create();
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
