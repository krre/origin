#pragma once
#include "../Core/Object.h"
#include <glm/glm.hpp>

class Color : public Object {

public:
    Color();
    Color(float r, float g, float b, float a = 1.0);
    glm::vec4 getRgba() const { return color; }
    glm::vec3 getRgb() const { return glm::vec3(color.r, color.g, color.b); }

private:
    glm::vec4 color;
};
