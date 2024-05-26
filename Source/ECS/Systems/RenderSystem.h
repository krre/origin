#pragma once
#include "ECS/System.h"
#include <vector>

class RenderSystem : public System {

public:
    RenderSystem(EntityManager* entityManager);
    void process(float dt) override;

private:

};
