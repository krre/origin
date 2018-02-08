#include "TextEdit.h"
#include "Rectangle.h"
#include "Label.h"
#include "Font.h"

namespace Origin {

const int DEFAULT_WIDHT = 200;
const Color BACKGROUND_COLOR = Color(0, 0, 0, 0.8);

TextEdit::TextEdit(Control* parent) : Control(parent) {
    background = new Rectangle(this);
    background->setColor(BACKGROUND_COLOR);

    label = new Label(this);
    label->setColor(Color(0.85, 0.85, 0.85));

    resize(DEFAULT_WIDHT, label->getFont()->getLineHeight());
}

void TextEdit::setText(const std::string& text) {
    label->setText(text);
}

const std::string& TextEdit::getText() const {
    return label->getText();
}

void TextEdit::resizeImpl(int width, int height) {
    background->resize(width, height);
}

} // Origin
