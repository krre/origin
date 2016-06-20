#include "Event.h"
#include "Input.h"

extern Input* input;

Event::Event() {

}

void Event::handleEvents() {
    ::input->mouseReset();
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
//                print("window resize: " << event.window.data1 << " " << event.window.data2);
                break;
            default:
                break;
            }
            break;

        case SDL_MOUSEMOTION:
            ::input->setMousePos(glm::ivec2(event.motion.x, event.motion.y));
            ::input->setRelMousePos(glm::ivec2(event.motion.xrel, event.motion.yrel));
            mouseMove.emit(event.motion.x, event.motion.y);
//            print("mouse move: " << event.motion.x << " " << event.motion.y);
            break;

        case SDL_MOUSEBUTTONDOWN:
            mouseButtonAction.emit(event.button);
//            print("mouse button down: " << event.button.button << " " << event.button.x << " " << event.button.y);
            break;

        case SDL_MOUSEBUTTONUP:
            mouseButtonAction.emit(event.button);
//            print("mouse button up: " << event.button.button << " " << event.button.x << " " << event.button.y);
            break;

        case SDL_MOUSEWHEEL:
//            print("mouse wheel: " << event.wheel.x << " " << event.wheel.y);
            break;

        case SDL_KEYDOWN:
            ::input->addKey(event.key.keysym.sym);
            keyPress.emit(event.key);
//            print("key down: " << event.key.keysym.sym);
            break;

        case SDL_KEYUP:
            ::input->removeKey(event.key.keysym.sym);
//            print("key up: " << event.key.keysym.sym);
            keyRelease.emit(event.key);

        default:
            break;
        }
    }
}
