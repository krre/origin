#pragma once
#include <core/Object.h>
#include <SDL_timer.h>

class Timer : public Core::Object {
public:
    Timer(Object* parent = nullptr);
    void start(int msec);
    void stop();

    Core::Signal<> timeout;

private:
    static Uint32 onTimeElaplsed(Uint32 interval, void* param);
    SDL_TimerID m_timerId;
};
