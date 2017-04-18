#include "Dialog.h"
#include "Scene/SceneManager.h"
#include "Event/Input.h"
#include "Core/App.h"

Dialog::Dialog() {
    SDL_SetRelativeMouseMode(SDL_FALSE);
    int centerX = App::get()->getWidth() / 2;
    int centerY = App::get()->getHeight() / 2;
    SDL_WarpMouseInWindow(App::get()->getWindow(), centerX, centerY);
//    int posX = centerX - getSize().width / 2;
//    int posY = centerY - getSize().height / 2;
//    setPosition({ posX, posY });
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
