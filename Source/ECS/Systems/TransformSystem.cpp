#include "TransformSystem.h"
#include "ECS/Components/TransformComponent.h"
#include "ECS/EntityManager.h"
#include "ECS/Entity.h"
#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/matrix_decompose.hpp>
#include <glm/gtx/quaternion.hpp>

namespace Origin {

TransformSystem::TransformSystem(EntityManager* entityManager) : System(entityManager) {
    type = System::Type::Transform;
}

void TransformSystem::process(float dt) {
    for (const auto& entity: entityManager->getEntities()) {
        update(entity.second.get());
    }
}

void TransformSystem::update(Entity* entity) {
    TransformComponent* tc = entity->getTransform();
    if (tc && tc->dirty) {
        glm::mat4 mat(1);
        glm::mat4 translationMatrix = glm::translate(mat, tc->position);
        glm::mat4 rotationMatrix = glm::toMat4(tc->rotation);
        glm::mat4 scaleMatrix = glm::scale(glm::mat4(1.0f), glm::vec3(tc->scale));
        tc->objectToWorld = translationMatrix * rotationMatrix * scaleMatrix;
        tc->worldToObject = glm::inverse(tc->objectToWorld);
        tc->dirty = false;
    }
}

void TransformSystem::setPosition(Entity* entity, const glm::vec3& position) {
    TransformComponent* tc = entity->getTransform();
    tc->position = position;
    tc->dirty = true;
}

void TransformSystem::setRotation(Entity* entity, float angle, const glm::vec3& axis) {
    TransformComponent* tc = entity->getTransform();
    tc->rotation = glm::toQuat(glm::rotate(glm::mat4(1.0f), angle, axis));
    tc->dirty = true;
}

void TransformSystem::setRotation(Entity* entity, const glm::quat& rotation) {
    TransformComponent* tc = entity->getTransform();
    tc->rotation = rotation;
    tc->dirty = true;
}

void TransformSystem::setScale(Entity* entity, float scale) {
    TransformComponent* tc = entity->getTransform();
    tc->scale = scale;
    tc->dirty = true;
}

void TransformSystem::setPitch(Entity* entity, float pitch) {
    TransformComponent* tc = entity->getTransform();
    tc->pitch = pitch;
    tc->dirty = true;
}

void TransformSystem::translate(Entity* entity, const glm::vec3& delta, bool local) {
    TransformComponent* tc = entity->getTransform();
    if (local) {
        tc->position += tc->rotation * delta;
    } else {
        tc->position += delta;
    }

    tc->dirty = true;
}

void TransformSystem::rotate(Entity* entity, const glm::quat& delta) {
    TransformComponent* tc = entity->getTransform();
    tc->rotation *= delta;
    tc->dirty = true;
}

void TransformSystem::scale(Entity* entity, float delta) {
    TransformComponent* tc = entity->getTransform();
    tc->scale *= delta;
    tc->dirty = true;
}

void TransformSystem::lookAt(Entity* entity, const glm::vec3& eye, const glm::vec3& center, const glm::vec3& up) {
    glm::mat4 m = glm::lookAt(eye, center, up);

    glm::vec3 scale;
    glm::quat rotation;
    glm::vec3 translation;
    glm::vec3 skew;
    glm::vec4 perspective;
    glm::decompose(glm::inverse(m), scale, rotation, translation, skew, perspective);

    TransformComponent* tc = entity->getTransform();
    tc->position = translation;
    tc->rotation = rotation;
    tc->dirty = true;
}

} // Origin
