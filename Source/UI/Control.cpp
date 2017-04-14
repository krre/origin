#include "Control.h"
#include <algorithm>

Control::Control() {

}

Control::Control(int width, int height) : size(width, height) {

}

void Control::addControl(std::shared_ptr<Control> control) {
    children.push_back(control);
    control->setParent(this);
}

void Control::removeControl(std::shared_ptr<Control> control) {
    children.erase(std::remove(children.begin(), children.end(), control), children.end());
}

void Control::clearControls() {
    children.clear();
}

void Control::setParent(Control* parent) {
    this->parent = parent;
}

void Control::setX(int x) {
    position.x = x;
}

void Control::setY(int y) {
    position.y = y;
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

void Control::markDirty() {
    dirty = true;
    if (parent != nullptr) {
        parent->markDirty();
    }
}

void Control::clearDirty() {
    dirty = false;
}
