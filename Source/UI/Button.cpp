#include "Button.h"

Button::Button() : Rectangle(100, 20) {
    setColor(glm::vec3(0.7, 0.7, 0.7));
}

void Button::setText(const std::__cxx11::string &text) {
    this->text = text;
}
