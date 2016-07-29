#include "PlayState.h"
#include "../ECS/Engine.h"
#include "../ECS/Systems/Systems.h"
#include <SDL.h>

PlayState::PlayState() {
    type = PLAY;
    isFreezable = true;
}

void PlayState::init() {

}

void PlayState::cleanup() {

}

void PlayState::pause() {

}

void PlayState::resume() {
    MovementControllerSystem* movementControllerSystem = static_cast<MovementControllerSystem*>(Engine::getInstance()->getSystem(SystemType::MovementController).get());
    movementControllerSystem->setActive(true);
    SDL_SetRelativeMouseMode(SDL_TRUE);
}

void PlayState::update(float dt) {

}

void PlayState::draw(float dt) {
    Engine::getInstance()->process(dt);
}
