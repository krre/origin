#include "Timer.h"

Timer::Timer(Object* parent) : Object(parent) {

}

void Timer::start(int msec) {
    m_timerId = SDL_AddTimer(msec, &Timer::onTimeElaplsed, this);
}

void Timer::stop() {
    SDL_RemoveTimer(m_timerId);
}

Uint32 Timer::onTimeElaplsed(Uint32 interval, void* param) {
    Timer* self = reinterpret_cast<Timer*>(param);
    self->timeout.fire();
    return 0;
}
