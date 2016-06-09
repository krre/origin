#pragma once
#include "../Core/Object.h"
#include <SDL.h>

class Event : public Object {

public:
    Event();
    void handleEvents();

    Signal<> quit;
    Signal<> render;
    Signal<double> update;
    Signal<int, int> windowResize;
    Signal<int, int> mouseMove;

private:

};
