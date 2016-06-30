#include "InputSystem.h"
#include "TransformSystem.h"
#include "../ECS/Engine.h"
#include "../Core/Game.h"
#include "../Event/Input.h"
#include "../Components/TransformComponent.h"

InputSystem::InputSystem() {
    type = SystemType::Input;
}

void InputSystem::process(float dt) {
    if (Game::getInstance()->getState() == Game::PAUSE) return;
    if (activeEntity) {
        moveActiveEntity(dt);
    }
}

void InputSystem::setActiveEntity(Entity* activeEntity) {
    this->activeEntity = activeEntity;
}

void InputSystem::moveActiveEntity(float dt) {
    const float MOVE_SPEED = 1.0f;
    const float ROTATE_SPEED = 0.1f;

    TransformComponent* tc = static_cast<TransformComponent*>(activeEntity->getComponent(ComponentType::Transform));

    ivec2 relMousePos = Input::getInstance()->getRelMousePos();
    tc->yaw += ROTATE_SPEED * relMousePos.x;
    tc->yaw = fmod(tc->yaw, 360.0f);

    tc->pitch -= ROTATE_SPEED * relMousePos.y;
    tc->pitch = clamp(tc->pitch, -80.0f, 80.0f);

    quat rotation = toQuat(eulerAngleYX(radians(tc->yaw), radians(tc->pitch)));
    TransformSystem* transformSystem = static_cast<TransformSystem*>(Engine::getInstance()->getSystem(SystemType::Transform));
    transformSystem->setRotation(activeEntity, rotation);

    if (Input::getInstance()->isKeyPressed(SDLK_w)) {
        transformSystem->translate(activeEntity, vec3(0.0f, 0.0f, -1.0f) * MOVE_SPEED * dt);
    } else if (Input::getInstance()->isKeyPressed(SDLK_s)) {
        transformSystem->translate(activeEntity, vec3(0.0f, 0.0f, 1.0f) * MOVE_SPEED * dt);
    } else if (Input::getInstance()->isKeyPressed(SDLK_a)) {
        transformSystem->translate(activeEntity, vec3(-1.0f, 0.0f, 0.0f) * MOVE_SPEED * dt);
    } else if (Input::getInstance()->isKeyPressed(SDLK_d)) {
        transformSystem->translate(activeEntity, vec3(1.0f, 0.0f, 0.0f) * MOVE_SPEED * dt);
    }
}
