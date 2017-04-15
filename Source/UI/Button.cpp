#include "Button.h"
#include "../Event/Event.h"

Button::Button() : Rectangle({ 100, 20 }) {
    setColor({ 0.6, 0.6, 0.6 });

    label = std::make_shared<Label>();
    addControl(label);
    label->setCenterControl(this);

    Event::get()->mouseButtonAction.connect<Button, &Button::onMouseButtonAction>(this);
}

Button::~Button() {
   Event::get()->mouseButtonAction.disconnect<Button, &Button::onMouseButtonAction>(this);
}

void Button::setText(const std::string &text) {
    label->setText(text);
    label->setZ(1.0f);
}

void Button::setLabelColor(const Color& labelColor) {
    label->setColor(labelColor);
}

void Button::prepareBatch(Batch2D* batch) {

}

void Button::draw(float dt) {

}

void Button::onMouseButtonAction(const SDL_MouseButtonEvent& event) {
    if (event.type == SDL_MOUSEBUTTONDOWN) {
        int mouseX = event.x;
        int mouseY = event.y;

        if (mouseX > position.x && mouseX < (position.x + size.width) && mouseY > position.y && mouseY < (position.y + size.height)) {
            clicked.emit();
        }
    }
}
