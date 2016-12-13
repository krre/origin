#include "MenuState.h"

MenuState::MenuState() : mainMenuScene(300, 300) {
    type = MENU;
    isFreezable = true;
}

void MenuState::init() {

}

void MenuState::cleanup() {

}

void MenuState::pause() {

}

void MenuState::resume() {

}

void MenuState::update(float dt) {

}

void MenuState::draw(float dt) {
    mainMenuScene.draw(dt);
}
