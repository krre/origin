#include "Control.h"

Control::Control(int width, int height) : size(width, height) {

}

void Control::setPosition(const glm::vec2& position) {
    this->position = position;
}

void Control::setSize(int width, int height) {
    size.x = width;
    size.y = height;
}

void Control::setScale(float scale) {
    this->scale = scale;
}

void Control::setZ(float z) {
    this->z = z;
}
