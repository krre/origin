#include "Dialog.h"
#include "../../Scene/SceneManager.h"
#include "../../Event/Input.h"
#include "../../Core/App.h"

Dialog::Dialog() {
    SDL_SetRelativeMouseMode(SDL_FALSE);
    SDL_WarpMouseInWindow(App::get()->getWindow(), App::get()->getWidth() / 2, App::get()->getHeight() / 2);
}

void Dialog::onKeyPressed(const SDL_KeyboardEvent& event) {
    if (event.keysym.sym == SDLK_ESCAPE) {
        SceneManager::get()->popScene();
        Input::get()->isKeyAccepted = true;
    }
}
