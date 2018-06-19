#pragma once
#include "Core/SingleObject.h"
#include "Core/Signal.h"
#include <SDL.h>

namespace Origin {

class Event : public SingleObject<Event> {

public:
    Event(Object* parent = nullptr);
    void handleEvents();

    Signal<int, int> windowResize;
    Signal<int, int> windowMove;
    Signal<int, int> mouseMove;
    Signal<const SDL_KeyboardEvent&> keyPressed;
    Signal<const SDL_KeyboardEvent&> keyRelease;
    Signal<const SDL_TextInputEvent&> textInput;
    Signal<const SDL_MouseButtonEvent&> mouseButtonAction;
};

} // Origin
