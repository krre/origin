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

void Dialog::keyPressed(const SDL_KeyboardEvent& event) {
    if (event.keysym.sym == SDLK_ESCAPE) {
        close();
    }
}

} // Origin
