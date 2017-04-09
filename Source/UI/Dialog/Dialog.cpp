#include "Dialog.h"
#include "../../Scene/SceneManager.h"
#include "../../Event/Input.h"
#include "../../Core/App.h"

Dialog::Dialog() {
    SDL_SetRelativeMouseMode(SDL_FALSE);
    SDL_WarpMouseInWindow(App::get()->getWindow(), App::get()->getWidth() / 2, App::get()->getHeight() / 2);
}

void Dialog::close() {
    SceneManager::get()->popScene();
}

void Dialog::onKeyPressed(const SDL_KeyboardEvent& event) {
    if (event.keysym.sym == SDLK_ESCAPE) {
        Input::get()->isKeyAccepted = true;
        close();
    }
}
