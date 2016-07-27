#include "PlayState.h"
#include "../ECS/Engine.h"

PlayState::PlayState() {
    type = PLAY;
}

void PlayState::init() {

}

void PlayState::cleanup() {

}

void PlayState::pause() {

}

void PlayState::resume() {

}

void PlayState::update(float dt) {

}

void PlayState::draw(float dt) {
    Engine::getInstance()->process(dt);
}
