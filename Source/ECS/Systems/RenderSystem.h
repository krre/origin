#pragma once
#include "ECS/System.h"
#include <vector>

namespace Origin {

class Drawable;

class RenderSystem : public System {

public:
    RenderSystem(EntityManager* entityManager);
    void process(float dt) override;

private:
    std::vector<Drawable*> drawables;
};

} // Origin
