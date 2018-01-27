#include "Rectangle.h"
#include "Core/Application.h"
#include "Resource/ResourceManager.h"
#include "Gui/Batch2D.h"
#include <glm/ext.hpp>

namespace Origin {

Rectangle::Rectangle(const Size& size, Control* parent) : Control(parent) {
    this->size = size;
}

Rectangle::Rectangle(const Pos2& position, const Size& size, Control* parent) : Control(parent) {
    this->position = position;
    this->size = size;
}

void Rectangle::setColor(const Color& color) {
    this->color = color;
}

void Rectangle::setBorderColor(const Color& borderColor) {
    this->borderColor = borderColor;
}

void Rectangle::setBorderWidth(uint32_t border) {
    this->borderWidth = border;
}

void Rectangle::prepareBatch(std::vector<Batch2D>& batches, std::vector<Batch2D::Vertex>& vertices) {
    Batch2D batch(&vertices);
    batch.color = color;
    batch.addQuad(position.x, position.y, size.width, size.height);

    batches.push_back(batch);
}

void Rectangle::drawImpl() {
}

} // Origin
