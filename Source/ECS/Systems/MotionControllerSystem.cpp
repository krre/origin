#include "MotionControllerSystem.h"
#include "../Components/MovementComponent.h"

MotionControllerSystem::MotionControllerSystem() {
    type = System::Type::MotionController;
}

void MotionControllerSystem::process(float dt) {

}

void MotionControllerSystem::setMoveEntity(Entity* moveEntity) {
    moveTarget = static_cast<TransformComponent*>(moveEntity->components[Component::Type::Transform].get());
    moveSpeed = static_cast<MovementComponent*>(moveEntity->components[Component::Type::Movement].get())->moveSpeed;
}

void MotionControllerSystem::setRotateEntity(Entity* rotateEntity) {
    rotateTarget = static_cast<TransformComponent*>(rotateEntity->components[Component::Type::Transform].get());
    rotateSpeed = static_cast<MovementComponent*>(rotateEntity->components[Component::Type::Movement].get())->rotateSpeed;
}
