#pragma once
#include "../System.h"

class InputSystem : public System {

public:
    InputSystem();
    void process(float dt) override;
    void setActiveEntity(Entity* activeEntity);
    Entity* getActiveEntity() const { return activeEntity; }

private:
    void moveActiveEntity(float dt);

    Entity* activeEntity = nullptr;
};
