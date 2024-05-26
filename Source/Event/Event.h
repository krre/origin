#pragma once
#include "Core/SingleObject.h"
#include "Core/Signal.h"
#include <SDL.h>

namespace Origin {

class Event : public Core::SingleObject<Event> {

public:
    Event(Object* parent = nullptr);
    void handleEvents();

    Core::Signal<int, int> windowResize;
    Core::Signal<int, int> windowMove;
    Core::Signal<int, int> mouseMove;
    Core::Signal<const SDL_KeyboardEvent&> keyPressed;
    Core::Signal<const SDL_KeyboardEvent&> keyRelease;
    Core::Signal<const SDL_TextInputEvent&> textInput;
    Core::Signal<const SDL_MouseButtonEvent&> mouseButtonAction;
};

} // Origin
