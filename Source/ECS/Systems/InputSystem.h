#pragma once
#include "../System.h"

class InputSystem : public System {

public:
    InputSystem();
    void process(float dt) override;
    void setActiveEntity(std::shared_ptr<Entity> activeEntity);
    std::shared_ptr<Entity> getActiveEntity() const { return activeEntity; }

private:
    void moveActiveEntity(float dt);

    std::shared_ptr<Entity> activeEntity = nullptr;
};
