#include "MovementControllerSystem.h"
#include "TransformSystem.h"
#include "../../Event/Input.h"
#include "../Components/MovementComponent.h"
#include "../Engine.h"

MovementControllerSystem::MovementControllerSystem() {
    type = SystemType::MovementController;
}

void MovementControllerSystem::process(float dt) {
    TransformComponent* tc = static_cast<TransformComponent*>(rotateEntity->components[ComponentType::Transform].get());

    glm::ivec2 relMousePos = Input::getInstance()->getRelMousePos();
    tc->yaw -= rotateSpeed * relMousePos.x;
    tc->yaw = fmod(tc->yaw, 360.0f);

    tc->pitch -= rotateSpeed * relMousePos.y;
    tc->pitch = glm::clamp(tc->pitch, -80.0f, 80.0f);

    glm::quat rotation = glm::toQuat(glm::eulerAngleYX(glm::radians(tc->yaw), glm::radians(tc->pitch)));
    TransformSystem* transformSystem = static_cast<TransformSystem*>(engine->getSystem(SystemType::Transform).get());
    transformSystem->setRotation(rotateEntity, rotation);

    if (Input::getInstance()->isKeyPressed(SDLK_w)) {
        transformSystem->translate(moveEntity, glm::vec3(0.0f, 0.0f, -1.0f) * moveSpeed * dt);
    } else if (Input::getInstance()->isKeyPressed(SDLK_s)) {
        transformSystem->translate(moveEntity, glm::vec3(0.0f, 0.0f, 1.0f) * moveSpeed * dt);
    } else if (Input::getInstance()->isKeyPressed(SDLK_a)) {
        transformSystem->translate(moveEntity, glm::vec3(-1.0f, 0.0f, 0.0f) * moveSpeed * dt);
    } else if (Input::getInstance()->isKeyPressed(SDLK_d)) {
        transformSystem->translate(moveEntity, glm::vec3(1.0f, 0.0f, 0.0f) * moveSpeed * dt);
    }

    // Track to floor pos
    TransformComponent* mtc = static_cast<TransformComponent*>(moveEntity->components[ComponentType::Transform].get());
    mtc->position.y = 0; // TODO: take from height map
}

void MovementControllerSystem::setMoveEntity(Entity* moveEntity) {
    this->moveEntity = moveEntity;
    moveSpeed = static_cast<MovementComponent*>(moveEntity->components[ComponentType::Movement].get())->moveSpeed;
}

void MovementControllerSystem::setRotateEntity(Entity* rotateEntity) {
    this->rotateEntity = rotateEntity;
    rotateSpeed = static_cast<MovementComponent*>(rotateEntity->components[ComponentType::Movement].get())->rotateSpeed;
}
