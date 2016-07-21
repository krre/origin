#pragma once
#include "Entity.h"

class EntityBuilder {

public:
    EntityBuilder() {}
    static std::shared_ptr<Entity> geometry();
    static std::shared_ptr<Entity> plane();
    static std::shared_ptr<Entity> cube();
    static std::shared_ptr<Entity> avatar();
    static std::shared_ptr<Entity> camera();
    static std::shared_ptr<Entity> freeCamera();
};
