#include "Dialog.h"
#include "ui/Overlay.h"
#include <SDL.h>

Dialog::Dialog() : Rectangle(Core::Size(200, 50)) {
    setColor(Color(0, 0, 0, 0.7));
}

void Dialog::close() {
    Overlay::get()->closeDialog(this);
}

void Dialog::resizeToContent() {
    if (!getChildren().size()) return;

    Control* child = static_cast<Control*>(getChildren().at(0));
    int width = child->getContentWidth() + padding * 2;
    int height = child->getContentHeight() + padding * 2;
    resize(width, height);

    child->move(padding, padding);
}

void Dialog::setPadding(int padding) {
    this->padding = padding;
}

void Dialog::keyPressed(const SDL_KeyboardEvent& event) {
    if (event.keysym.sym == SDLK_ESCAPE) {
        close();
    }
}
