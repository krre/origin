#include "Control.h"
#include "Batch2D.h"
#include <algorithm>

namespace Origin {

Control::Control(Control* parent) : parent(parent) {
    if (parent != nullptr) {
        parent->addChild(this);
    }
}

Control::~Control() {
    if (parent != nullptr) {
        parent->removeChild(this);
    }

    for (const auto& control : children) {
        delete control;
    }
}

void Control::setPosition(const Pos2& position) {
    this->position = position;
    if (parent != nullptr) {
        absolutePosition = static_cast<Control*>(parent)->absolutePosition + position;
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

void Control::resize(int width, int height) {
    size.width = width;
    size.height = height;
}

void Control::setZ(float z) {
    this->z = z;
}

void Control::markDirty() {
    isDirty = true;
    if (parent != nullptr) {
        static_cast<Control*>(parent)->markDirty();
    }
}

void Control::clearDirty() {
    isDirty = false;
}

void Control::setVisible(bool visible) {
    this->visible = visible;
}

void Control::setParent(Control* parent) {
    if (this->parent == parent) return;

    // Remove self from children of previous parent
    if (this->parent != nullptr) {
        this->parent->removeChild(this);
    }

    this->parent = parent;

    if (parent != nullptr) {
        parent->addChild(this);
    }
}

void Control::addChild(Control* control) {
    children.push_back(control);
    control->setParent(this);
}

void Control::removeChild(Control* control) {
    children.erase(std::remove(children.begin(), children.end(), control), children.end());
}

} // Origin
