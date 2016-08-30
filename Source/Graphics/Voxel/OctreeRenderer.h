#pragma once
#include "../../Core/Object.h"
#include "Octree.h"
#include <glm/glm.hpp>
#include <vector>

class RenderSurface;

class OctreeRenderer : public Object {

public:
    struct Ray {
        glm::vec3 origin;
        glm::vec3 direction;
    };

    struct AABB {
        glm::vec3 min;
        glm::vec3 max;
    };

    OctreeRenderer();
    void render(const RenderSurface* renderSurface);

private:
    bool rayAABBIntersect(Ray* ray, AABB* aabb, float& t);
    bool renderOnlyFirst = false; // for debug
};
