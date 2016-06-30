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

void TransformSystem::setRotation(Entity* entity, float angle, vec3& axis) {
    TransformComponent* tc = static_cast<TransformComponent*>(entity->getComponent(ComponentType::Transform));
    tc->rotation = toQuat(glm::rotate(mat4(1.0f), angle, axis));
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

void TransformSystem::translate(Entity* entity, vec3& delta, bool local) {
    TransformComponent* tc = static_cast<TransformComponent*>(entity->getComponent(ComponentType::Transform));
    if (local) {
        tc->position += tc->rotation * delta;
    } else {
        tc->position += delta;
    }

    tc->dirty = true;
}

void TransformSystem::rotate(Entity* entity, quat& delta) {
    TransformComponent* tc = static_cast<TransformComponent*>(entity->getComponent(ComponentType::Transform));
    tc->rotation *= delta;
    tc->dirty = true;
}

void TransformSystem::scale(Entity* entity, vec3& scale) {
    TransformComponent* tc = static_cast<TransformComponent*>(entity->getComponent(ComponentType::Transform));
    tc->scale = scale;
    tc->dirty = true;
}
