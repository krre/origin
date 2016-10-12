#pragma once
#include "../../Core/Common.h"
#include "../../ECS/Entity.h"

class GPUMemoryManager {

public:
    GPUMemoryManager();
    void addEntity(const Entity* entity);
    void updateEntityOctree(const Entity* entity);
    void removeEntity(const Entity* entity);
};
