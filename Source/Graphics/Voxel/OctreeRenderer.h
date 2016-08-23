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

    OctreeRenderer();
    void render(const RenderSurface* renderSurface);

private:
    bool rayOctreeIntersect(Ray* ray, Octree* octree);
    void updateCubeTransform(const glm::mat4& matrix);
    bool renderOnlyFirst = false; // for debug
    Ray ray;
    std::vector<glm::vec4> cubeVerticles;
};
