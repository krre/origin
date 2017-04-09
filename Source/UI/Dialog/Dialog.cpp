#include "Dialog.h"
#include "../../Scene/SceneManager.h"
#include "../../Event/Input.h"

Dialog::Dialog() {

}

void Dialog::onKeyPressed(const SDL_KeyboardEvent& event) {
    if (event.keysym.sym == SDLK_ESCAPE) {
        SceneManager::get()->popScene();
        Input::get()->isKeyAccepted = true;
    }
}
