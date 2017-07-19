#include "Control.h"
#include "Batch2D.h"
#include <algorithm>

Control::Control() {

}

Control::Control(const Pos2& position) : position(position) {

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

void Control::getBatches(std::vector<std::unique_ptr<Batch2D>>& batches, VertexBuffer* vertexBuffer, IndexBuffer* indexBuffer) {
    std::unique_ptr<Batch2D> batch = std::unique_ptr<Batch2D>(new Batch2D);
    prepareBatch(batch.get(), vertexBuffer, indexBuffer);

    for (const auto& control : children) {
        control->getBatches(batches, vertexBuffer, indexBuffer);
    }

    batches.push_back(std::move(batch));

    clearDirty();
}
