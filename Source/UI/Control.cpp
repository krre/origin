#include "Control.h"

Control::Control(int width, int height) : width(width), height(height) {

}

void Control::setPosition(const glm::vec2& position) {
    this->position = position;
}

void Control::setWidth(int width) {
    this->width = width;
}

void Control::setHeight(int height) {
    this->height = height;
}

void Control::resize(int width, int height) {
    this->width = width;
    this->height = height;
}

void Control::setZ(float z) {
    this->z = z;
}
