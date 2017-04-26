#include "Label.h"
#include "Core/App.h"
#include "Resource/ResourceManager.h"
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

Label::Label() {
    setFont(ResourceManager::get()->load<Font>("Fonts/inconsolata.fnt"));
}

void Label::setText(const std::string& text) {
    this->text = text;
    updateTextData();
}

void Label::setFont(Font* font) {
    this->font = font;
}

void Label::setColor(const Color& color) {
    this->color = color;
}

void Label::draw(float dt) {

}

void Label::update(float dt) {

}

void Label::prepareBatch(Batch2D* batch, VertexBuffer* vertexBuffer, IndexBuffer* indexBuffer) {

}

void Label::updateTextData() {

}
