#include "Engine.h"

Engine::Engine() {

}

void Engine::addSystem(const System* system) {
    systems.push_back(system);
}

void Engine::removeSystem(const System* system) {
    systems.remove(system);
}

void Engine::clearSystems() {
    systems.clear();
}
