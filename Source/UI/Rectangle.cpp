#include "Rectangle.h"
#include "Core/Game.h"
#include "Screen/Screen.h"
#include "UI/UIRenderer.h"
#include "Resource/ResourceManager.h"
#include "Graphics/Render/RenderManager.h"
#include "UIBatch.h"
#include "Font.h"
#include <glm/ext.hpp>

namespace Origin {

Rectangle::Rectangle(Control* parent) : Control(parent) {
    font = Game::getResourceManager()->load<Font>("Fonts/inconsolatalgc.ttf");
}

Rectangle::Rectangle(const Size& size, Control* parent) : Rectangle(parent) {
    this->size = size;
}

Rectangle::Rectangle(const Pos2& position, const Size& size, Control* parent) : Rectangle(size, parent) {
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
    UIBatch batch(Game::getRenderManager()->getUIRenderer()->getVerticles());
    batch.color = color;
    batch.texture = font->getTexture();
    batch.addQuad(absolutePosition.x, absolutePosition.y, size.width, size.height, font);
    Game::getRenderManager()->getUIRenderer()->addBatch(batch);
}

} // Origin
