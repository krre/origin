#include "TransformSystem.h"
#include "../Components/TransformComponent.h"
#include "../Engine.h"

TransformSystem::TransformSystem() {
    type = System::Type::Transform;
}

void TransformSystem::process(float dt) {
    for (auto entity: engine->getEntities()) {
        TransformComponent* tc = static_cast<TransformComponent*>(engine->getComponent(entity.get(), Component::Type::Transform));
        if (tc && tc->dirty) {
            glm::mat4 translationMatrix = glm::translate(tc->translation);
            glm::mat4 rotationMatrix = glm::toMat4(tc->rotation);
            glm::mat4 scaleMatrix = glm::scale(glm::mat4(1.0f), tc->scale);
            tc->localMatrix = rotationMatrix * translationMatrix * scaleMatrix;
            tc->dirty = false;
        }
    }
}

void TransformSystem::setPosition(Entity* entity, glm::vec3& position) {
    TransformComponent* tc = static_cast<TransformComponent*>(engine->getComponent(entity, Component::Type::Transform));
    tc->translation = position;
    tc->dirty = true;
}

void TransformSystem::setRotation(Entity* entity, float angle, glm::vec3& axis) {
    TransformComponent* tc = static_cast<TransformComponent*>(engine->getComponent(entity, Component::Type::Transform));
    tc->rotation = toQuat(glm::rotate(glm::mat4(1.0f), angle, axis));
    tc->dirty = true;
}

void TransformSystem::setRotation(std::shared_ptr<Entity> entity, glm::quat& rotation) {
    TransformComponent* tc = static_cast<TransformComponent*>(engine->getComponent(entity.get(), Component::Type::Transform));
    tc->rotation = rotation;
    tc->dirty = true;
}

void TransformSystem::setScale(std::shared_ptr<Entity> entity, glm::vec3& scale) {
    TransformComponent* tc = static_cast<TransformComponent*>(engine->getComponent(entity.get(), Component::Type::Transform));
    tc->scale = scale;
    tc->dirty = true;
}

void TransformSystem::translate(std::shared_ptr<Entity> entity, const glm::vec3& delta, bool local) {
    TransformComponent* tc = static_cast<TransformComponent*>(engine->getComponent(entity.get(), Component::Type::Transform));
    if (local) {
        tc->translation += tc->rotation * delta;
    } else {
        tc->translation += delta;
    }

    tc->dirty = true;
}

void TransformSystem::rotate(std::shared_ptr<Entity> entity, glm::quat& delta) {
    TransformComponent* tc = static_cast<TransformComponent*>(engine->getComponent(entity.get(), Component::Type::Transform));
    tc->rotation *= delta;
    tc->dirty = true;
}

void TransformSystem::scale(std::shared_ptr<Entity> entity, glm::vec3& delta) {
    TransformComponent* tc = static_cast<TransformComponent*>(engine->getComponent(entity.get(), Component::Type::Transform));
    tc->scale *= delta;
    tc->dirty = true;
}
