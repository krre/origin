#include "PauseState.h"
#include "../ECS/Engine.h"
#include "../ECS/Systems/Systems.h"
#include <SDL.h>

PauseState::PauseState() : GameState(PAUSE), pauseScene(300, 200) {
    isFreezable = true;
}

void PauseState::init() {
    pauseScene.init();
    pauseScene.create();
}

void PauseState::cleanup() {

}

void PauseState::pause() {

}

void PauseState::resume() {
    SDL_SetRelativeMouseMode(SDL_FALSE);
    MovementControllerSystem* movementControllerSystem = static_cast<MovementControllerSystem*>(Engine::get()->getSystem(SystemType::MovementController).get());
    movementControllerSystem->setActive(false);
}

void PauseState::draw(float dt) {
    pauseScene.draw(dt);
}

void PauseState::update(float dt) {
    pauseScene.update(dt);
}
