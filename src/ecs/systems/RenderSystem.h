#pragma once
#include "ecs/System.h"

class RenderSystem : public System {

public:
    RenderSystem(EntityManager* entityManager);
    void process(float dt) override;

private:

};
