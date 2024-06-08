#pragma once
#include "ecs/System.h"

class Entity;

class MovementControllerSystem : public System {

public:
    MovementControllerSystem(EntityManager* entityManager);
    void process(float dt) override;
    void setMoveEntity(Entity* moveEntity);
    void setRotateEntity(Entity* rotateEntity);

private:
    Entity* m_moveEntity = nullptr;
    Entity* m_rotateEntity = nullptr;

    float m_moveSpeed;
    float m_rotateSpeed;
};
