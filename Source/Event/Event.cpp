#include "Event.h"
#include "Input.h"

Event::Event() {

}

void Event::handleEvents() {
    Input::getInstance()->mouseReset();
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
            Input::getInstance()->setMousePos(glm::ivec2(event.motion.x, event.motion.y));
            Input::getInstance()->setRelMousePos(glm::ivec2(event.motion.xrel, event.motion.yrel));
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
            Input::getInstance()->addKey(event.key.keysym.sym);
            keyPressed.emit(event.key);
//            print("key down: " << event.key.keysym.sym);
            break;

        case SDL_KEYUP:
            Input::getInstance()->removeKey(event.key.keysym.sym);
//            print("key up: " << event.key.keysym.sym);
            keyRelease.emit(event.key);

        default:
            break;
        }
    }
}
