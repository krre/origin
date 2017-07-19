#pragma once
#include "ECS/System.h"
#include <vector>

class Drawable;

class RenderSystem : public System {

public:
    RenderSystem();
    void process(float dt) override;

private:
    std::vector<Drawable*> drawables;
};
