#pragma once
#include "../Core/Object.h"
#include <glm/glm.hpp>

class Color : public Object {

public:
    Color();
    Color(float red, float green, float blue, float alpha = 1.0);
    glm::vec4 getRgba() const { return glm::vec4(red, green, blue, alpha); }
    glm::vec3 getRgb() const { return glm::vec3(red, green, blue); }

private:
    float red = 0;
    float green = 0;
    float blue = 0;
    float alpha = 0;
};
