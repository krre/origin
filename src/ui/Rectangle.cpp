#include "Rectangle.h"
#include "graphics/render/UIRenderer.h"
#include "resource/ResourceManager.h"
#include "UIBatch.h"
#include "Font.h"
#include <glm/ext.hpp>

Rectangle::Rectangle(Control* parent) : Control(parent) {
    m_font = ResourceManager::get()->load<Font>("fonts/inconsolatalgc.ttf");
}

Rectangle::Rectangle(const Core::Size& size, Control* parent) : Rectangle(parent) {
    this->m_size = size;
}

Rectangle::Rectangle(const Core::Pos2& position, const Core::Size& size, Control* parent) : Rectangle(size, parent) {
    this->m_position = position;
}

void Rectangle::setColor(const Color& color) {
    this->m_color = color;
}

void Rectangle::setBorderColor(const Color& borderColor) {
    this->m_borderColor = borderColor;
}

void Rectangle::setBorderWidth(uint32_t border) {
    this->m_borderWidth = border;
}

void Rectangle::drawImpl() {
    UIBatch batch(UIRenderer::get()->verticles());
    batch.color = m_color;
    batch.texture = m_font->texture();
    batch.addQuad(m_absolutePosition.x, m_absolutePosition.y, m_size.width, m_size.height, m_font);
    UIRenderer::get()->addBatch(batch);
}
