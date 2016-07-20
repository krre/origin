#pragma once
#include "../Core/Object.h"
#include "../ECS/Entity.h"
#include <vector>

class Renderer : public Object {

public:
    Renderer();
    void render(Entity* entity);
};
