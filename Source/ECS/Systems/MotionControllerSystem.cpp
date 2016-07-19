#include "MotionControllerSystem.h"

MotionControllerSystem::MotionControllerSystem() {
    type = System::Type::MotionController;
}

void MotionControllerSystem::process(float dt) {

}

void MotionControllerSystem::setMoveEntity(Entity* moveEntity) {
    moveTarget = static_cast<TransformComponent*>(moveEntity->components[Component::Type::Transform].get());
}

void MotionControllerSystem::setRotateEntity(Entity* rotateEntity) {
    rotateTarget = static_cast<TransformComponent*>(rotateEntity->components[Component::Type::Transform].get());
}
