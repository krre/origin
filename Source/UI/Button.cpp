#include "Button.h"
#include "Event/Event.h"
#include "Core/Game.h"
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
    clickedId = Game::getEvent()->mouseButtonAction.connect(this, &Button::onMouseButtonAction);
}

Button::~Button() {
    Game::getEvent()->mouseButtonAction.disconnect(clickedId);
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

void Button::onMouseButtonAction(const SDL_MouseButtonEvent& event) {
    if (!visible) return;

    if (event.type == SDL_MOUSEBUTTONDOWN) {
        int mouseX = event.x;
        int mouseY = event.y;

        if (mouseX > absolutePosition.x && mouseX < (absolutePosition.x + size.width) && mouseY > absolutePosition.y && mouseY < (absolutePosition.y + size.height)) {
            clicked.fire();
        }
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
