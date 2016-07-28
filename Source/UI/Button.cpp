#include "Button.h"

Button::Button() : Rectangle(100, 20) {
    setColor(glm::vec3(0.6, 0.6, 0.6));
}

void Button::setText(const std::__cxx11::string &text) {
    this->text = text;
    labelText.setText(text);
}

void Button::draw(float dt) {
    Rectangle::draw(dt);
    labelText.setPosition(glm::vec2(position.x + 10, position.y + 15));
    labelText.draw(dt);
}
