#include "TransformSystem.h"
#include "../Components/TransformComponent.h"

TransformSystem::TransformSystem() {
    type = SystemType::Transform;
}

void TransformSystem::process(float dt) {

}

void TransformSystem::setPosition(Entity* entity, vec3& position) {
    TransformComponent* tc = static_cast<TransformComponent*>(entity->getComponent(ComponentType::Transform));
    tc->position = position;
    tc->dirty = true;
}

void TransformSystem::setRotation(Entity *entity, float angle, vec3& axis) {
    TransformComponent* tc = static_cast<TransformComponent*>(entity->getComponent(ComponentType::Transform));
    tc->rotation = toQuat(rotate(mat4(1.0f), angle, axis));
    tc->dirty = true;
}

void TransformSystem::setRotation(Entity* entity, quat& rotation) {
    TransformComponent* tc = static_cast<TransformComponent*>(entity->getComponent(ComponentType::Transform));
    tc->rotation = rotation;
    tc->dirty = true;
}

void TransformSystem::setScale(Entity* entity, vec3& scale) {
    TransformComponent* tc = static_cast<TransformComponent*>(entity->getComponent(ComponentType::Transform));
    tc->scale = scale;
    tc->dirty = true;
}
