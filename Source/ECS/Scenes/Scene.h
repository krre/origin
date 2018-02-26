#pragma once
#include "Core/Object.h"
#include <glm/glm.hpp>

namespace Origin {

class Entity;

class Scene : public Object {

public:
    Scene(Object* parent = nullptr);
    ~Scene();

    void setEntity(Entity* entity);
    Entity* getEntity() const { return entity; }

private:
    Entity* entity = nullptr;
};

} // Origin
