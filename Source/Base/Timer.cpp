#include "Timer.h"

namespace Origin {

Timer::Timer(Object* parent) : Object(parent) {

}

void Timer::start(int msec) {
    timerId = SDL_AddTimer(msec, &Timer::onTimeElaplsed, this);
}

void Timer::stop() {
    SDL_RemoveTimer(timerId);
}

Uint32 Timer::onTimeElaplsed(Uint32 interval, void* param) {
    Timer* self = reinterpret_cast<Timer*>(param);
    self->timeout.fire();
    return 0;
}

} // Origin
