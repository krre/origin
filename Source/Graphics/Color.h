#pragma once
#include "../Core/Object.h"
#include <glm/glm.hpp>

using namespace glm;

class Color : public Object {

public:
    Color();
    Color(int r, int g, int b, int a = 255);
    vec4 getRgba() const { return color; }

private:
    vec4 color;
};
