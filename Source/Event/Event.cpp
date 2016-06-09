#include "Event.h"

Event::Event() {

}

void Event::handleEvents() {
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
                print("window resize: " << event.window.data1 << " " << event.window.data2);
                break;
            default:
                break;
            }
            break;

        case SDL_MOUSEMOTION:
            print("mouse move: " << event.motion.x << " " << event.motion.y);
            break;

        case SDL_MOUSEBUTTONDOWN:
            print("mouse button down: " << event.button.button << " " << event.button.x << " " << event.button.y);
            break;

        case SDL_MOUSEBUTTONUP:
            print("mouse button up: " << event.button.button << " " << event.button.x << " " << event.button.y);
            break;

        case SDL_MOUSEWHEEL:
            print("mouse wheel: " << event.wheel.x << " " << event.wheel.y);

        default:
            break;
        }
    }
}
