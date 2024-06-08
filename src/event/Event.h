#pragma once
#include <core/SingleObject.h>
#include <core/Signal.h>

struct SDL_KeyboardEvent;
struct SDL_TextInputEvent;
struct SDL_MouseButtonEvent;

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
