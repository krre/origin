#include "Event.h"
#include "Input.h"

Event::Event() {

}

void Event::handleEvents() {
    Input::get()->mouseReset();
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        switch (event.type) {

        case SDL_QUIT:
            quit.emit();
            break;

        case SDL_WINDOWEVENT:
            switch (event.window.event) {
            case SDL_WINDOWEVENT_RESIZED:
                windowResize.emit(event.window.data1, event.window.data2);
                break;
            case SDL_WINDOWEVENT_MOVED:
                windowMove.emit(event.window.data1, event.window.data2);
//                winMove.emit(event.window.data1, event.window.data2);
                break;
            default:
                break;
            }
            break;

        case SDL_MOUSEMOTION:
            Input::get()->setMousePos(glm::ivec2(event.motion.x, event.motion.y));
            Input::get()->setRelMousePos(glm::ivec2(event.motion.xrel, event.motion.yrel));
            mouseMove.emit(event.motion.x, event.motion.y);
            break;

        case SDL_MOUSEBUTTONDOWN:
            mouseButtonAction.emit(event.button);
            break;

        case SDL_MOUSEBUTTONUP:
            mouseButtonAction.emit(event.button);
            break;

        case SDL_MOUSEWHEEL:
            break;

        case SDL_KEYDOWN:
            // Use keyLock to fix bug on some Linux system, when catch two SDL_KEYDOWN event and one SDL_KEYUP
            if (!keyLock) {
                Input::get()->addKey(event.key.keysym.sym);
                Input::get()->isKeyAccepted = false;
                keyPressed.emit(event.key);
                keyLock = true;
            }
            break;

        case SDL_KEYUP:
            Input::get()->removeKey(event.key.keysym.sym);
            Input::get()->isKeyAccepted = false;
            keyRelease.emit(event.key);
            keyLock = false;
        default:
            break;
        }
    }
}
