#include "TextEdit.h"
#include "Rectangle.h"
#include "Label.h"
#include "Font.h"

#undef HAVE_STDINT_H
#include <SDL_keycode.h>
#include <SDL_events.h>

const int DEFAULT_WIDHT = 200;
const Color BACKGROUND_COLOR = Color(0, 0, 0, 0.8);

TextEdit::TextEdit(Control* parent) : Control(parent) {
    m_background = new Rectangle(this);
    m_background->setColor(BACKGROUND_COLOR);

    m_label = new Label(this);
    m_label->setColor(Color(0.85, 0.85, 0.85));

    resize(DEFAULT_WIDHT, m_label->font()->lineHeight() + 6);
    // Align to vertical center
    m_label->move(5, size().height / 2 - 2);
}

void TextEdit::setText(const std::string& text) {
    m_label->setText(text);
}

const std::string& TextEdit::text() const {
    return m_label->text();
}

void TextEdit::resizeImpl(int width, int height) {
    m_background->resize(width, height);
}

void TextEdit::keyPressed(const SDL_KeyboardEvent& event) {
    if (event.keysym.sym == SDLK_BACKSPACE) {
        std::string text = m_label->text();
        std::string newText = text.substr(0, text.length() - 1);
        m_label->setText(newText);
    }
}

void TextEdit::textPressed(const SDL_TextInputEvent& event) {
    m_label->setText(m_label->text() + event.text);
}

void TextEdit::mouseButtonAction(const SDL_MouseButtonEvent& event) {
    if (event.type == SDL_MOUSEBUTTONDOWN) {
        activate();
    }
}
