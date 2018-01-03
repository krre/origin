#pragma once
#include "Core/Singleton.h"
#include <Core/Signal.h>
#include <SDL.h>

namespace Origin {

class Event : public Singleton<Event> {

public:
    Event();
    void handleEvents();

    Signal<> quit;
    Signal<> render;
    Signal<double> update;
    Signal<int, int> windowResize;
    Signal<int, int> windowMove;
    Signal<int, int> mouseMove;
    Signal<const SDL_KeyboardEvent&> keyPressed;
    Signal<const SDL_KeyboardEvent&> keyRelease;
    Signal<const SDL_MouseButtonEvent&> mouseButtonAction;

private:
    bool keyLock = false;
};

} // Origin
