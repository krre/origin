#include "Object.h"
#include <assert.h>

namespace Origin {

Object::Object(Object* parent) {
    setParent(parent);
}

Object::~Object() {
    setParent(nullptr);

    for (int i = data.children.size() - 1; i >= 0; i--) {
        delete data.children.at(i);
    }
}

void Object::setParent(Object* parent) {
    if (data.parent == parent) return;

    // Remove self from children of previous parent
    if (data.parent) {
        data.parent->removeChild(this);
    }

    if (parent) {
        parent->addChild(this);
    }

    data.parent = parent;
}

void Object::addChild(Object* child) {
    assert(child);
    data.children.push_back(child);
    polishAddChild(child);
}

void Object::insertChild(Object* child, int index) {
    data.children.insert(data.children.begin() + index, child);
    polishAddChild(child);
}

void Object::removeChild(Object* child) {
    data.children.erase(std::remove(data.children.begin(), data.children.end(), child), data.children.end());
    child->data.parent = nullptr;
    notifyRemoveChild(child);
}

void Object::removeChild(int index) {
    Object* child = data.children.at(index);
    removeChild(child);
}

void Object::removeChildren() {
    for (int i = 0; i < data.children.size(); i++) {
        data.children.at(i)->data.parent = nullptr;
    }

    data.children.clear();
}

void Object::polishAddChild(Object* child) {
    // Remove child from children of previous parent
    if (child->data.parent) {
        child->data.parent->removeChild(child);
    }
    child->data.parent = this;
    notifyAddChild(child);
}

} // Origin
