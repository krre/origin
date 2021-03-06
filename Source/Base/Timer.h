#pragma once
#include "Core/Object.h"
#include <SDL_timer.h>

namespace Origin {

class Timer : public Object {

public:
    Timer(Object* parent = nullptr);
    void start(int msec);
    void stop();

    Signal<> timeout;

private:
    static Uint32 onTimeElaplsed(Uint32 interval, void* param);
    SDL_TimerID timerId;
};

} // Origin
