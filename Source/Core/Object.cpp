#include "Object.h"
#include <assert.h>

namespace Origin {

Object::Object(Object* parent) {
    setParent(parent);
}

Object::~Object() {
    removeChildren();

    if (parent != nullptr) {
        parent->removeChild(this);
    }
}

void Object::setParent(Object* parent) {
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

void Object::addChild(Object* child) {
    children.push_back(child);
    child->setParent(this);
}

void Object::insertChild(Object* child, int index) {
    assert(index >= 0 && index < children.size());
    children.insert(children.begin() + index, child);
}

void Object::removeChild(Object* child) {
    children.erase(std::remove(children.begin(), children.end(), child), children.end());
}

void Object::removeChild(int index) {
    children.erase(children.begin() + index);
}

void Object::removeChildren() {
    for (int i = children.size() - 1; i >= 0; i--) {
        delete children.at(i);
    }

    children.clear();
}

} // Origin
