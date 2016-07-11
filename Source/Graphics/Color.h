#pragma once
#include "../Core/Object.h"
#include <glm/glm.hpp>

class Color : public Object {

public:
    Color();
    Color(int r, int g, int b, int a = 255);
    glm::vec4 getRgba() const { return color; }

private:
    glm::vec4 color;
};
