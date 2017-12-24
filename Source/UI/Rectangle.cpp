#include "Rectangle.h"
#include "Core/Application.h"
#include "Resource/ResourceManager.h"
#include <glm/ext.hpp>

Rectangle::Rectangle(const Size& size) {
    this->size = size;
}

Rectangle::Rectangle(const Pos2& position, const Size& size) {
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

void Rectangle::prepareBatch(Batch2D* batch, VertexBuffer* vertexBuffer, IndexBuffer* indexBuffer) {

}
