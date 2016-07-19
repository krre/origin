#pragma once
#include "../Core/Object.h"
#include "../ECS/Entity.h"
#include <vector>

class Renderer : public Object {

public:
    Renderer();
    void render(float dt);
    void setEntities(std::vector<std::shared_ptr<Entity>> *entities);

private:
    std::vector<std::shared_ptr<Entity>>* entities = nullptr;
};
