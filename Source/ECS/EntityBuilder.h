#pragma once
#include "Entity.h"

class EntityBuilder {

public:
    EntityBuilder() {}
    static std::shared_ptr<Entity> ground();
    static std::shared_ptr<Entity> avatar();
    static std::shared_ptr<Entity> camera();
    static std::shared_ptr<Entity> freeCamera();
};
