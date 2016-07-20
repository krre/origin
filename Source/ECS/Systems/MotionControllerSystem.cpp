#include "MotionControllerSystem.h"
#include "TransformSystem.h"
#include "../Event/Input.h"
#include "../Components/MovementComponent.h"
#include "../Engine.h"

MotionControllerSystem::MotionControllerSystem() {
    type = System::Type::MotionController;
}

void MotionControllerSystem::process(float dt) {
    TransformComponent* tc = static_cast<TransformComponent*>(rotateEntity->components[Component::Type::Transform].get());

    glm::ivec2 relMousePos = Input::getInstance()->getRelMousePos();
    tc->yaw += rotateSpeed * relMousePos.x;
    tc->yaw = fmod(tc->yaw, 360.0f);

    tc->pitch -= rotateSpeed * relMousePos.y;
    tc->pitch = glm::clamp(tc->pitch, -80.0f, 80.0f);

    glm::quat rotation = glm::toQuat(glm::eulerAngleYX(glm::radians(tc->yaw), glm::radians(tc->pitch)));
    TransformSystem* transformSystem = static_cast<TransformSystem*>(engine->getSystem(System::Type::Transform).get());
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
}

void MotionControllerSystem::setMoveEntity(Entity* moveEntity) {
    this->moveEntity = moveEntity;
    moveSpeed = static_cast<MovementComponent*>(moveEntity->components[Component::Type::Movement].get())->moveSpeed;
}

void MotionControllerSystem::setRotateEntity(Entity* rotateEntity) {
    this->rotateEntity = rotateEntity;
    rotateSpeed = static_cast<MovementComponent*>(rotateEntity->components[Component::Type::Movement].get())->rotateSpeed;
}
