#include "Dialog.h"
#include "Event/Input.h"
#include "Core/Game.h"
#include "Core/Window.h"

namespace Origin {

Dialog::Dialog() : Rectangle(Size(200, 50)) {
    setColor(Color(0, 0, 0, 0.7));
}

void Dialog::close() {
}

//void Dialog::onKeyPressed(const SDL_KeyboardEvent& event) {
//    if (event.keysym.sym == SDLK_ESCAPE) {
//        Input::get()->isKeyAccepted = true;
//        close();
//    }
//}

} // Origin
