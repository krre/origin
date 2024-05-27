#include "Event.h"
#include "Input.h"
#include "Base/Game.h"
#include <SDL.h>

Event::Event(Object* parent) : SingleObject(parent) {

}

void Event::handleEvents() {
    Input::get()->mouseReset();
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        switch (event.type) {
            case SDL_QUIT:
                Game::quit();
                break;
            case SDL_WINDOWEVENT:
                switch (event.window.event) {
                    case SDL_WINDOWEVENT_RESIZED:
                        windowResize.fire(event.window.data1, event.window.data2);
                        break;
                    default:
                        break;
                    }
                break;
            case SDL_MOUSEMOTION:
                Input::get()->setMousePos(glm::ivec2(event.motion.x, event.motion.y));
                Input::get()->setRelMousePos(glm::ivec2(event.motion.xrel, event.motion.yrel));
                mouseMove.fire(event.motion.x, event.motion.y);
                break;
            case SDL_MOUSEBUTTONDOWN:
                mouseButtonAction.fire(event.button);
                break;
            case SDL_MOUSEBUTTONUP:
                mouseButtonAction.fire(event.button);
                break;
            case SDL_MOUSEWHEEL:
                break;
            case SDL_KEYDOWN:
                Input::get()->addKey(event.key.keysym.sym);
                Input::get()->isKeyAccepted = false;
                keyPressed.fire(event.key);
                break;
            case SDL_KEYUP:
                Input::get()->removeKey(event.key.keysym.sym);
                Input::get()->isKeyAccepted = false;
                keyRelease.fire(event.key);
                break;
            case SDL_TEXTINPUT:
                textInput.fire(event.text);
                break;
            case SDL_TEXTEDITING:
//                PRINT("edit " << event.edit.text);
                break;
            default:
                break;
        }
    }
}
