#include "Event.h"
#include "Input.h"
#include "base/Game.h"
#include <SDL3/SDL.h>

Event::Event(Object* parent) : SingleObject(parent) {

}

void Event::handleEvents() {
    Input::get()->mouseReset();
    SDL_Event event;

    while (SDL_PollEvent(&event)) {
        switch (event.type) {
            case SDL_EVENT_QUIT:
                Game::quit();
                break;
            case SDL_EVENT_WINDOW_RESIZED:
                windowResize.fire(event.window.data1, event.window.data2);
                break;
            case SDL_EVENT_MOUSE_MOTION:
                Input::get()->setMousePos(glm::ivec2(event.motion.x, event.motion.y));
                Input::get()->setRelMousePos(glm::ivec2(event.motion.xrel, event.motion.yrel));
                mouseMove.fire(event.motion.x, event.motion.y);
                break;
            case SDL_EVENT_MOUSE_BUTTON_DOWN:
                mouseButtonAction.fire(event.button);
                break;
            case SDL_EVENT_MOUSE_BUTTON_UP:
                mouseButtonAction.fire(event.button);
                break;
            case SDL_EVENT_MOUSE_WHEEL:
                break;
            case SDL_EVENT_KEY_DOWN:
                Input::get()->addKey(event.key.key);
                Input::get()->isKeyAccepted = false;
                keyPressed.fire(event.key);
                break;
            case SDL_EVENT_KEY_UP:
                Input::get()->removeKey(event.key.key);
                Input::get()->isKeyAccepted = false;
                keyRelease.fire(event.key);
                break;
            case SDL_EVENT_TEXT_INPUT:
                textInput.fire(event.text);
                break;
            case SDL_EVENT_TEXT_EDITING:
                // TODO
                break;
            default:
                break;
        }
    }
}
