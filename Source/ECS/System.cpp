#include "System.h"
#include "Engine.h"
#include <algorithm>

Engine* System::engine;

System::System() {
    engine = Engine::get();
}

bool System::setActive(bool active) {
    this->active = active;
}
