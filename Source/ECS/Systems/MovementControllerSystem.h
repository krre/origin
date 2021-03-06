#pragma once
#include "ECS/System.h"

namespace Origin {

class Entity;

class MovementControllerSystem : public System {

public:
    MovementControllerSystem(EntityManager* entityManager);
    void process(float dt) override;
    void setMoveEntity(Entity* moveEntity);
    void setRotateEntity(Entity* rotateEntity);

private:
    Entity* moveEntity = nullptr;
    Entity* rotateEntity = nullptr;

    float moveSpeed;
    float rotateSpeed;
};

} // Origin
