#include "Color.h"

Color::Color() : color(glm::vec4(1.0, 1.0, 1.0, 1.0)) {

}

Color::Color(int r, int g, int b, int a) : color(glm::vec4(r, g, b, a)) {

}
