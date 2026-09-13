#pragma once
#include <core/Object.h>
#include <core/Signal.h>
#include <SDL3/SDL_timer.h>

class Timer : public Core::Object {
public:
    Timer(Object* parent = nullptr);
    void start(int msec);
    void stop();

    Core::Signal<> timeout;

private:
    static Uint32 onTimeElaplsed(void* userdata, SDL_TimerID timerID, Uint32 interval);
    SDL_TimerID m_timerId;
};
