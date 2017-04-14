#include "Control.h"
#include <algorithm>

Control::Control() {

}

Control::Control(const Pos2& position) : position(position) {

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

void Control::setPosition(const Pos2& position) {
    this->position = position;
    if (parent != nullptr) {
        absolutePosition = parent->absolutePosition + position;
    } else {
        absolutePosition = position;
    }
}

void Control::setSize(const Size& size) {
    this->size = size;
}

void Control::setScale(float scale) {
    this->scale = scale;
}

void Control::setFillControl(Control* fillControl) {
    this->fillControl = fillControl;
}

void Control::setCenterControl(Control* centerControl) {
    this->centerControl = centerControl;
}

void Control::setZ(float z) {
    this->z = z;
}

void Control::markDirty() {
    isDirty = true;
    if (parent != nullptr) {
        parent->markDirty();
    }
}

void Control::clearDirty() {
    isDirty = false;
}
