#include "Button.h"
#include "Label.h"
#include <SDL.h>

Button::Button(Control* parent) : Rectangle(parent) {
    m_label = new Label(this);
    setTextColor(Color::WHITE);
    setColor({ 0, 0, 0, 0.7 });
    resize(100, 30);
}

Button::Button(const std::string& text, Control* parent) : Button(parent) {
    setText(text);
}

void Button::setText(const std::string &text) {
    m_label->setText(text);
    centerLabel();
}

std::string Button::text() const {
    return m_label->text();
}

void Button::setTextColor(const Color& labelColor) {
    m_label->setColor(labelColor);
}

const Color& Button::textColor() const {
    return m_label->color();
}

void Button::mouseButtonAction(const SDL_MouseButtonEvent& event) {
    if (event.type == SDL_MOUSEBUTTONDOWN) {
        clicked.fire();
    }
}

void Button::centerLabel() {
    int x = (m_size.width - m_label->contentWidth()) / 2;
    int y = (m_size.height - m_label->contentHeight()) / 2;
    m_label->move(x, y);
}

void Button::resizeImpl(int width, int height) {
    centerLabel();
}
