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
    for (auto control : children) {
        delete control;
    }
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

void Control::getBatches(std::vector<std::unique_ptr<Batch2D>>& batches, VertexBuffer* vertexBuffer, IndexBuffer* indexBuffer) {
    std::unique_ptr<Batch2D> batch = std::make_unique<Batch2D>();
    prepareBatch(batch.get(), vertexBuffer, indexBuffer);

    for (auto child : children) {
        child->getBatches(batches, vertexBuffer, indexBuffer);
    }

    batches.push_back(std::move(batch));

    clearDirty();
}

void Control::setParent(Control* parent) {
    this->parent = parent;
}

void Control::addChild(Control* control) {
    children.push_back(control);
    control->setParent(this);
}

void Control::removeChild(Control* control) {
    children.erase(std::remove(children.begin(), children.end(), control), children.end());
}

} // Origin
