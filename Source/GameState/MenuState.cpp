#include "MenuState.h"

MenuState::MenuState() : GameState(MENU) {
    isFreezable = true;
}

void MenuState::init() {
    menuScene.init();
    menuScene.create();
}

void MenuState::cleanup() {

}

void MenuState::pause() {

}

void MenuState::resume() {

}

void MenuState::update(float dt) {
    menuScene.update(dt);
}

void MenuState::draw(float dt) {
    menuScene.draw(dt);
}
