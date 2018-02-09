#include "Dialog.h"
#include "Event/Input.h"
#include "Core/Game.h"
#include "Core/Window.h"
#include "UI/Overlay.h"
#include "Screen/Screen.h"

namespace Origin {

Dialog::Dialog() : Rectangle(Size(200, 50)) {
    setColor(Color(0, 0, 0, 0.7));
}

void Dialog::close() {
    Game::getOverlay()->closeDialog(this);
}

void Dialog::resizeToContent() {
    if (!children.size()) return;

    Control* child = children.at(0);
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

} // Origin
