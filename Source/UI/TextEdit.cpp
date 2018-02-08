#include "TextEdit.h"
#include "Rectangle.h"
#include "Label.h"
#include "Font.h"

#undef HAVE_STDINT_H
#include <SDL_keycode.h>
#include <SDL_events.h>

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

void TextEdit::keyPressed(const SDL_KeyboardEvent& event) {
    if (event.keysym.sym == SDLK_BACKSPACE) {
        std::string text = label->getText();
        std::string newText = text.substr(0, text.length() - 1);
        label->setText(newText);
    }
}

void TextEdit::textPressed(const SDL_TextInputEvent& event) {
    label->setText(label->getText() + event.text);
}

} // Origin
