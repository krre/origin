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
    m_type = System::Type::MovementController;
}

void MovementControllerSystem::process(float dt) {
    if (!m_rotateEntity || !m_moveEntity) return;

    TransformComponent* tc = m_rotateEntity->transform();

    glm::ivec2 relMousePos = Input::get()->relMousePos();
    tc->yaw -= m_rotateSpeed * relMousePos.x;
    tc->yaw = fmod(tc->yaw, 360.0f);

    tc->pitch -= m_rotateSpeed * relMousePos.y;
    tc->pitch = glm::clamp(tc->pitch, -80.0f, 80.0f);

    glm::quat rotation = glm::toQuat(glm::eulerAngleYX(glm::radians(tc->yaw), glm::radians(tc->pitch)));
    TransformSystem* transformSystem = static_cast<TransformSystem*>(m_entityManager->system(System::Type::Transform).get());
    transformSystem->setRotation(m_rotateEntity, rotation);

    if (Input::get()->isKeyPressed(SDLK_w)) {
        transformSystem->translate(m_moveEntity, glm::vec3(0.0f, 0.0f, -1.0f) * m_moveSpeed * dt);
    } else if (Input::get()->isKeyPressed(SDLK_s)) {
        transformSystem->translate(m_moveEntity, glm::vec3(0.0f, 0.0f, 1.0f) * m_moveSpeed * dt);
    } else if (Input::get()->isKeyPressed(SDLK_a)) {
        transformSystem->translate(m_moveEntity, glm::vec3(-1.0f, 0.0f, 0.0f) * m_moveSpeed * dt);
    } else if (Input::get()->isKeyPressed(SDLK_d)) {
        transformSystem->translate(m_moveEntity, glm::vec3(1.0f, 0.0f, 0.0f) * m_moveSpeed * dt);
    }

    bool free = m_moveEntity->movement()->free;
    if (!free) {
        // Track to floor pos
        TransformComponent* mtc = m_moveEntity->transform();
        mtc->position.y = 0; // TODO: take from height map
    }
}

void MovementControllerSystem::setMoveEntity(Entity* moveEntity) {
    m_moveEntity = moveEntity;
    m_moveSpeed = moveEntity->movement()->moveSpeed;
}

void MovementControllerSystem::setRotateEntity(Entity* rotateEntity) {
    m_rotateEntity = rotateEntity;
    m_rotateSpeed = rotateEntity->movement()->rotateSpeed;
}
