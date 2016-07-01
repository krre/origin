#include "TransformSystem.h"
#include "../Components/TransformComponent.h"
#include "../Engine.h"

TransformSystem::TransformSystem() {
    type = SystemType::Transform;
}

void TransformSystem::process(float dt) {
    for (auto entity: Engine::getInstance()->getEntities()) {
        TransformComponent* tc = static_cast<TransformComponent*>(entity->getComponent(ComponentType::Transform));
        if (tc && tc->dirty) {
            mat4 translationMatrix = glm::translate(tc->translation);
            mat4 rotationMatrix = glm::toMat4(tc->rotation);
            mat4 scaleMatrix = glm::scale(mat4(1.0f), tc->scale);
            tc->localMatrix = rotationMatrix * translationMatrix * scaleMatrix;
            tc->dirty = false;
        }
    }
}

void TransformSystem::setPosition(Entity* entity, vec3& position) {
    TransformComponent* tc = static_cast<TransformComponent*>(entity->getComponent(ComponentType::Transform));
    tc->translation = position;
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

void TransformSystem::translate(Entity* entity, const vec3& delta, bool local) {
    TransformComponent* tc = static_cast<TransformComponent*>(entity->getComponent(ComponentType::Transform));
    if (local) {
        tc->translation += tc->rotation * delta;
    } else {
        tc->translation += delta;
    }

    tc->dirty = true;
}

void TransformSystem::rotate(Entity* entity, quat& delta) {
    TransformComponent* tc = static_cast<TransformComponent*>(entity->getComponent(ComponentType::Transform));
    tc->rotation *= delta;
    tc->dirty = true;
}

void TransformSystem::scale(Entity* entity, vec3& delta) {
    TransformComponent* tc = static_cast<TransformComponent*>(entity->getComponent(ComponentType::Transform));
    tc->scale *= delta;
    tc->dirty = true;
}
