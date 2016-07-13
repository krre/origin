#pragma once
#include "../Core/Object.h"
#include "../ECS/Entity.h"
#include <vector>

class Renderer : public Object {

public:
    Renderer();
    void render(float dt);
    void setEntities(std::vector<Entity*>* entities);

private:
    std::vector<Entity*>* entities = nullptr;
};
