#pragma once
#include "Core/Object.h"
#include <glm/glm.hpp>

namespace Origin {

class Color : public Core::Object {

public:
    Color();
    Color(float red, float green, float blue, float alpha = 1.0);
    glm::vec4 getRgba() const;
    glm::vec3 getRgb() const;
    uint32_t getArgb() const { return color; }

    float getRed() const;
    float getGreen() const;
    float getBlue() const;
    float getAlpha() const;

    static const Color TRANSPARENT;
    static const Color BLACK;
    static const Color WHITE;
    static const Color GRAY;
    static const Color RED;
    static const Color GREEN;
    static const Color BLUE;

private:
    uint32_t color = 0;
};

} // Origin
