#include "Object.h"
#include <assert.h>
#include <algorithm>

namespace Core {

Object::Object(Object* parent) {
    setParent(parent);
}

Object::~Object() {
    setParent(nullptr);

    for (int i = m_children.size() - 1; i >= 0; i--) {
        delete m_children.at(i);
    }
}

void Object::setParent(Object* parent) {
    if (this->m_parent == parent) return;

    // Remove self from children of previous parent
    if (this->m_parent) {
        this->m_parent->removeChild(this);
    }

    if (parent) {
        parent->appendChild(this);
    }

    this->m_parent = parent;
}

void Object::appendChild(Object* child) {
    assert(child);
    m_children.push_back(child);
    polishAppendChild(child);
}

void Object::insertChild(Object* child, int index) {
    m_children.insert(m_children.begin() + index, child);
    polishAppendChild(child);
}

void Object::removeChild(Object* child) {
    m_children.erase(std::remove(m_children.begin(), m_children.end(), child), m_children.end());
    child->m_parent = nullptr;
    notifyRemoveChild(child);
}

void Object::removeChild(int index) {
    Object* child = m_children.at(index);
    removeChild(child);
}

void Object::removeChildren() {
    for (auto child : m_children) {
        child->m_parent = nullptr;
    }

    m_children.clear();
}

void Object::polishAppendChild(Object* child) {
    // Remove child from children of previous parent
    if (child->m_parent) {
        child->m_parent->removeChild(child);
    }
    child->m_parent = this;
    notifyAddChild(child);
}

}
