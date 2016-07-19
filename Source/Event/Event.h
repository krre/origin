#pragma once
#include "../Core/Singleton.h"
#include <SDL.h>

class Event : public Singleton<Event> {

public:
    Event();
    void handleEvents();

    Nano::Signal<void()> quit;
    Nano::Signal<void()> render;
    Nano::Signal<void(double)> update;
    Nano::Signal<void(int, int)> windowResize;
    Nano::Signal<void(int, int)> mouseMove;
    Nano::Signal<void(const SDL_KeyboardEvent&)> keyPress;
    Nano::Signal<void(const SDL_KeyboardEvent&)> keyRelease;
    Nano::Signal<void(const SDL_MouseButtonEvent&)> mouseButtonAction;

private:

};
