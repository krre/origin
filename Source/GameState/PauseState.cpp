#include "PauseState.h"

PauseState::PauseState() : pauseScene(300, 200) {
    type = PAUSE;
    isFreezable = true;
}

void PauseState::init() {

}

void PauseState::cleanup() {

}

void PauseState::pause() {

}

void PauseState::resume() {

}

void PauseState::draw(float dt) {
    pauseScene.draw(dt);
}

void PauseState::update(float dt) {

}
