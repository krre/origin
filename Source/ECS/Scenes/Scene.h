#pragma once
#include "Core/Object.h"
#include <glm/glm.hpp>

namespace Origin {

class Entity;

class Scene : public Object {

public:

    struct Vertex {
        glm::vec4 pos;
        glm::vec4 color;
    };

    Scene(Object* parent = nullptr);
    ~Scene();

    void setEntity(Entity* entity);
    Entity* getEntity() const { return entity; }

private:
    Entity* entity = nullptr;
};

} // Origin
