#include "MovementControllerSystem.h"
#include "TransformSystem.h"
#include "event/Input.h"
#include "ecs/components/MovementComponent.h"
#include "ecs/components/TransformComponent.h"
#include "ecs/EntityManager.h"
#include "ecs/Entity.h"
#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/quaternion.hpp>
#include <glm/gtx/euler_angles.hpp>

MovementControllerSystem::MovementControllerSystem(EntityManager* entityManager) : System(entityManager) {
    type = System::Type::MovementController;
}

void MovementControllerSystem::process(float dt) {
    if (!rotateEntity || !moveEntity) return;

    TransformComponent* tc = rotateEntity->getTransform();

    glm::ivec2 relMousePos = Input::get()->getRelMousePos();
    tc->yaw -= rotateSpeed * relMousePos.x;
    tc->yaw = fmod(tc->yaw, 360.0f);

    tc->pitch -= rotateSpeed * relMousePos.y;
    tc->pitch = glm::clamp(tc->pitch, -80.0f, 80.0f);

    glm::quat rotation = glm::toQuat(glm::eulerAngleYX(glm::radians(tc->yaw), glm::radians(tc->pitch)));
    TransformSystem* transformSystem = static_cast<TransformSystem*>(entityManager->getSystem(System::Type::Transform).get());
    transformSystem->setRotation(rotateEntity, rotation);

    if (Input::get()->isKeyPressed(SDLK_w)) {
        transformSystem->translate(moveEntity, glm::vec3(0.0f, 0.0f, -1.0f) * moveSpeed * dt);
    } else if (Input::get()->isKeyPressed(SDLK_s)) {
        transformSystem->translate(moveEntity, glm::vec3(0.0f, 0.0f, 1.0f) * moveSpeed * dt);
    } else if (Input::get()->isKeyPressed(SDLK_a)) {
        transformSystem->translate(moveEntity, glm::vec3(-1.0f, 0.0f, 0.0f) * moveSpeed * dt);
    } else if (Input::get()->isKeyPressed(SDLK_d)) {
        transformSystem->translate(moveEntity, glm::vec3(1.0f, 0.0f, 0.0f) * moveSpeed * dt);
    }

    bool free = moveEntity->getMovement()->free;
    if (!free) {
        // Track to floor pos
        TransformComponent* mtc = moveEntity->getTransform();
        mtc->position.y = 0; // TODO: take from height map
    }
}

void MovementControllerSystem::setMoveEntity(Entity* moveEntity) {
    this->moveEntity = moveEntity;
    moveSpeed = moveEntity->getMovement()->moveSpeed;
}

void MovementControllerSystem::setRotateEntity(Entity* rotateEntity) {
    this->rotateEntity = rotateEntity;
    rotateSpeed = rotateEntity->getMovement()->rotateSpeed;
}
