#pragma once
#include "Core/Object.h"
#include <glm/glm.hpp>

namespace Origin {

class Entity;

class Scene : public Object {

public:
    Scene(Object* parent = nullptr);
    ~Scene();

    void setRootEntity(Entity* rootEntity);
    Entity* getRootEntity() const { return rootEntity; }

private:
    Entity* rootEntity = nullptr;
};

} // Origin
