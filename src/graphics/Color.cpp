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
    m_color = (a << 24) | (r << 16) | (g << 8) | b;
}

glm::vec4 Color::rgba() const {
    return glm::vec4(red(), green(), blue(), alpha());
}

glm::vec3 Color::rgb() const {
    return glm::vec3(red(), green(), blue());
}

float Color::red() const {
    return ((m_color >> 16) & 0xFF) / 255.0;
}

float Color::green() const {
    return ((m_color >> 8) & 0xFF) / 255.0;
}

float Color::blue() const {
    return (m_color & 0xFF) / 255.0;
}

float Color::alpha() const {
    return ((m_color >> 24) & 0xFF) / 255.0;
}
