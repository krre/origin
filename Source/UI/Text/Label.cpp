#include "Label.h"
#include "Core/Application.h"
#include "Resource/ResourceManager.h"
#include "UI/Text/Font.h"
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

Label::Label() {
//    setFont(ResourceManager::get()->load<Font>("Fonts/inconsolata.fnt"));
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

void Label::prepareBatch(Batch2D* batch, VertexBuffer* vertexBuffer, IndexBuffer* indexBuffer) {

}

void Label::updateTextData() {

}
