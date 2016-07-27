#include "Rectangle.h"

Rectangle::Rectangle(int width, int height) :
    Control(width, height),
    plane(1.0, 1.0) {

}

void Rectangle::draw(float dt) {

}

void Rectangle::setColor(const glm::vec3& color) {
    this->color = color;
}
