#include "Engine.h"

Engine::Engine() {

}

void Engine::addSystem(System* system) {
    systems.push_back(system);
}

void Engine::removeSystem(System* system) {
    systems.remove(system);
}

void Engine::clearSystems() {
    systems.clear();
}

void Engine::addEntity(Entity* entity) {
    entities.push_back(entity);
}

void Engine::removeEntity(Entity* entity) {
    entities.remove(entity);
}

Entity* Engine::getEntity(EntityId id) {
    for (auto it: entities) {
        if (it->getId() == id) {
            return it;
        }
    }

    return nullptr;
}

void Engine::clearEntities() {
    entities.clear();
}

void Engine::process(float dt) {
    for (auto it: systems) {
        it->process(dt);
    }
}
