#pragma once
#include <core/Object.h>
#include <glm/glm.hpp>

class Color : public Core::Object {

public:
    Color();
    Color(float red, float green, float blue, float alpha = 1.0);

    glm::vec4 rgba() const;
    glm::vec3 rgb() const;
    uint32_t argb() const { return color; }

    float red() const;
    float green() const;
    float blue() const;
    float alpha() const;

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
