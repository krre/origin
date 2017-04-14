#include "Rectangle.h"
#include "../Core/App.h"
#include "../Resource/ResourceManager.h"
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

void Rectangle::setBorder(uint32_t border) {
    this->border = border;
}

void Rectangle::draw(float dt) {
}

void Rectangle::update(float dt) {

}
