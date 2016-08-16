#pragma once
#include "../../Core/Object.h"
#include <glm/glm.hpp>

class RenderSurface;

class OctreeRenderer : public Object {

public:
    struct Ray {
        glm::vec3 origin;
        glm::vec3 direction;
    };

    OctreeRenderer();
    void render(const RenderSurface* renderSurface);

private:
    Ray ray;
};
