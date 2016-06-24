#include "Engine.h"

Engine::Engine() {

}

void Engine::addSystem(System* system) {
    systems.push_back(system);
}

void Engine::removeSystem(System *system) {
    systems.remove(system);
}

void Engine::clearSystems() {
    systems.clear();
}

void Engine::update(float dt) {
    for (auto it: systems) {
        it->update(dt);
    }
}
