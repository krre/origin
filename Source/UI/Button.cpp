#include "Button.h"
#include "Event/Event.h"
#include "Text/Label.h"

Button::Button() : Rectangle({ 100, 20 }) {
    setColor({ 0.6, 0.6, 0.6 });

    label = std::make_shared<Label>();
    addChild(label);
    label->setCenterControl(this);

    clickedId = Event::get()->mouseButtonAction.connect(this, &Button::onMouseButtonAction);
}

Button::~Button() {
   Event::get()->mouseButtonAction.disconnect(clickedId);
}

void Button::setText(const std::string &text) {
    label->setText(text);
    label->setZ(1.0f);
}

std::string Button::getText() const {
    return label->getText();
}

void Button::setLabelColor(const Color& labelColor) {
    label->setColor(labelColor);
}

const Color& Button::getLabelColor() const {
    return label->getColor();
}

void Button::prepareBatch(Batch2D* batch, VertexBuffer* vertexBuffer, IndexBuffer* indexBuffer) {

}

void Button::draw(float dt) {

}

void Button::onMouseButtonAction(const SDL_MouseButtonEvent& event) {
    if (event.type == SDL_MOUSEBUTTONDOWN) {
        int mouseX = event.x;
        int mouseY = event.y;

        if (mouseX > position.x && mouseX < (position.x + size.width) && mouseY > position.y && mouseY < (position.y + size.height)) {
            clicked.fire();
        }
    }
}
