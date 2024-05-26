#include "Color.h"
#include <glm/common.hpp>

const Color Color::TRANSPARENT = { 0.0, 0.0, 0.0, 0.0 };
const Color Color::BLACK = { 0.0, 0.0, 0.0, 1.0 };
const Color Color::WHITE = { 1.0, 1.0, 1.0, 1.0 };
const Color Color::GRAY =  { 0.5, 0.5, 0.5, 1.0 };
const Color Color::RED =   { 1.0, 0.0, 0.0 , 1.0};
const Color Color::GREEN = { 0.0, 1.0, 0.0, 1.0 };
const Color Color::BLUE =  { 0.0, 0.0, 1.0, 1.0 };

Color::Color() {

}

Color::Color(float red, float green, float blue, float alpha) {
    uint32_t r = glm::clamp(red, 0.0f, 1.0f) * 255;
    uint32_t g = glm::clamp(green, 0.0f, 1.0f) * 255;
    uint32_t b = glm::clamp(blue, 0.0f, 1.0f) * 255;
    uint32_t a = glm::clamp(alpha, 0.0f, 1.0f) * 255;
    color = (a << 24) | (r << 16) | (g << 8) | b;
}

glm::vec4 Color::getRgba() const {
    return glm::vec4(getRed(), getGreen(), getBlue(), getAlpha());
}

glm::vec3 Color::getRgb() const {
    return glm::vec3(getRed(), getGreen(), getBlue());
}

float Color::getRed() const {
    return ((color >> 16) & 0xFF) / 255.0;
}

float Color::getGreen() const {
    return ((color >> 8) & 0xFF) / 255.0;
}

float Color::getBlue() const {
    return (color & 0xFF) / 255.0;
}

float Color::getAlpha() const {
    return ((color >> 24) & 0xFF) / 255.0;
}
