#pragma once
#include "ECS/System.h"
#include <vector>

namespace Origin {

class RenderSystem : public System {

public:
    RenderSystem(EntityManager* entityManager);
    void process(float dt) override;

private:

};

} // Origin
