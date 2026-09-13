#include "Timer.h"

Timer::Timer(Object* parent) : Object(parent) {

}

void Timer::start(int msec) {
    m_timerId = SDL_AddTimer(msec, &Timer::onTimeElaplsed, this);
}

void Timer::stop() {
    SDL_RemoveTimer(m_timerId);
}

Uint32 Timer::onTimeElaplsed(void* userdata, SDL_TimerID timerID, Uint32 interval) {
    Timer* self = reinterpret_cast<Timer*>(userdata);
    self->timeout.fire();
    return 0;
}
