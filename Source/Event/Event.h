#pragma once
#include <Core/Signal.h>
#include <SDL.h>

namespace Origin {

class Event {

public:
    Event();
    void handleEvents();

    Signal<> render;
    Signal<double> update;
    Signal<int, int> windowResize;
    Signal<int, int> windowMove;
    Signal<int, int> mouseMove;
    Signal<const SDL_KeyboardEvent&> keyPressed;
    Signal<const SDL_KeyboardEvent&> keyRelease;
    Signal<const SDL_TextInputEvent&> textInput;
    Signal<const SDL_MouseButtonEvent&> mouseButtonAction;

private:
    bool keyLock = false;
};

} // Origin
