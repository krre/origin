#include "Rectangle.h"
#include "Core/Game.h"
#include "Screen/Screen.h"
#include "UI/UIRenderer.h"
#include "Resource/ResourceManager.h"
#include "UIBatch.h"
#include "Font.h"
#include <glm/ext.hpp>

namespace Origin {

Rectangle::Rectangle(const Size& size, Control* parent) : Control(parent) {
    this->size = size;
    font = Game::getResourceManager()->load<Font>("Fonts/inconsolatalgc.ttf");
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

void Rectangle::drawImpl() {
    UIBatch batch(Game::getUIRenderer()->getVerticles());
    batch.color = color;
    batch.texture = font->getTexture();
    batch.addQuad(absolutePosition.x, absolutePosition.y, size.width, size.height, font);
    Game::getUIRenderer()->addBatch(batch);
}

} // Origin
