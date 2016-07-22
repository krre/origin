#pragma once
#include "Entity.h"

class EntityBuilder {

public:
    EntityBuilder() {}
    // Geometry
    static std::shared_ptr<Entity> geometry();
    static std::shared_ptr<Entity> plane();
    static std::shared_ptr<Entity> cube();

    // Camera
    static std::shared_ptr<Entity> camera();
    static std::shared_ptr<Entity> freeCamera();

    // Light
    static std::shared_ptr<Entity> light();

    static std::shared_ptr<Entity> avatar();
};
