#include "Object.h"
#include <assert.h>

namespace Origin {

Object::Object(Object* parent) {
    setParent(parent);
}

Object::~Object() {
    setParent(nullptr);

    for (int i = children.size() - 1; i >= 0; i--) {
        delete children.at(i);
    }
}

void Object::setParent(Object* parent) {
    if (this->parent == parent) return;

    // Remove self from children of previous parent
    if (this->parent) {
        this->parent->removeChild(this);
    }

    if (parent) {
        parent->addChild(this);
    }

    this->parent = parent;
}

void Object::addChild(Object* child) {
    assert(child);
    children.push_back(child);
    polishAddChild(child);
}

void Object::insertChild(Object* child, int index) {
    children.insert(children.begin() + index, child);
    polishAddChild(child);
}

void Object::removeChild(Object* child) {
    children.erase(std::remove(children.begin(), children.end(), child), children.end());
    child->parent = nullptr;
    notifyRemoveChild(child);
}

void Object::removeChild(int index) {
    Object* child = children.at(index);
    removeChild(child);
}

void Object::removeChildren() {
    for (int i = 0; i < children.size(); i++) {
        children.at(i)->parent = nullptr;
    }

    children.clear();
}

void Object::polishAddChild(Object* child) {
    // Remove child from children of previous parent
    if (child->parent) {
        child->parent->removeChild(child);
    }
    child->parent = this;
    notifyAddChild(child);
}

} // Origin
