#pragma once
#include "../../Core/Object.h"
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
    void updateCubeTransform(const glm::mat4& matrix);

    Ray ray;
    std::vector<glm::vec4> cubeVerticles;
};
