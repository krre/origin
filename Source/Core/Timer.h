#pragma once
#include "Object.h"
#include <SDL_timer.h>

class Timer : public Object {

public:
    Timer();
    void start(int msec);
    void stop();

    Nano::Signal<void()> timeout;

private:
    static Uint32 onTimeElaplsed(Uint32 interval, void* param);
    SDL_TimerID timerId;
};
