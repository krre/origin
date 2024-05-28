#include "Rectangle.h"
#include "graphics/render/UIRenderer.h"
#include "resource/ResourceManager.h"
#include "UIBatch.h"
#include "Font.h"
#include <glm/ext.hpp>

Rectangle::Rectangle(Control* parent) : Control(parent) {
    font = ResourceManager::get()->load<Font>("fonts/inconsolatalgc.ttf");
}

Rectangle::Rectangle(const Core::Size& size, Control* parent) : Rectangle(parent) {
    this->size = size;
}

Rectangle::Rectangle(const Core::Pos2& position, const Core::Size& size, Control* parent) : Rectangle(size, parent) {
    this->position = position;
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

void Rectangle::drawImpl() {
    UIBatch batch(UIRenderer::get()->getVerticles());
    batch.color = color;
    batch.texture = font->getTexture();
    batch.addQuad(absolutePosition.x, absolutePosition.y, size.width, size.height, font);
    UIRenderer::get()->addBatch(batch);
}
