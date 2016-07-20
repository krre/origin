#include "Color.h"

Color::Color() : color(glm::vec4(1.0, 1.0, 1.0, 1.0)) {

}

Color::Color(float r, float g, float b, float a) : color(glm::vec4(r, g, b, a)) {

}
