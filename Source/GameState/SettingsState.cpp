#include "SettingsState.h"

SettingsState::SettingsState() : menuScene(300, 300) {
    type = SETTINGS;
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

}

void SettingsState::draw(float dt) {
    menuScene.draw(dt);
}
