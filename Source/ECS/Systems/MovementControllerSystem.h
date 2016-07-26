#pragma once
#include "../System.h"
#include "../Entity.h"
#include "../Components/TransformComponent.h"

class MovementControllerSystem : public System {

public:
    MovementControllerSystem();
    void process(float dt) override;
    void setMoveEntity(Entity* moveEntity);
    void setRotateEntity(Entity* rotateEntity);

private:
    Entity* moveEntity;
    Entity* rotateEntity;

    float moveSpeed;
    float rotateSpeed;
};
