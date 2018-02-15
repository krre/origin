#include "Button.h"
#include "Event/Event.h"
#include "Base/Game.h"
#include "Base/Window.h"
#include "Label.h"

namespace Origin {

Button::Button(Control* parent) : Rectangle(parent) {
    label = new Label(this);
    setTextColor(Color::WHITE);
    setColor({ 0, 0, 0, 0.7 });
    resize(100, 30);
}

Button::Button(const std::string& text, Control* parent) : Button(parent) {
    setText(text);
}

Button::~Button() {
}

void Button::setText(const std::string &text) {
    label->setText(text);
    centerLabel();
}

std::string Button::getText() const {
    return label->getText();
}

void Button::setTextColor(const Color& labelColor) {
    label->setColor(labelColor);
}

const Color& Button::getTextColor() const {
    return label->getColor();
}

void Button::mouseButtonAction(const SDL_MouseButtonEvent& event) {
    if (event.type == SDL_MOUSEBUTTONDOWN) {
        clicked.fire();
    }
}

void Button::centerLabel() {
    int x = (size.width - label->getContentWidth()) / 2;
    int y = (size.height - label->getContentHeight()) / 2;
    label->move(x, y);
}

void Button::resizeImpl(int width, int height) {
    centerLabel();
}

} // Origin
