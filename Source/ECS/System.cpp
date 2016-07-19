#include "System.h"
#include "Engine.h"
#include <algorithm>

Engine* System::engine;

System::System() {
    engine = Engine::getInstance();
}

void System::addEntity(std::shared_ptr<Entity> entity) {
    entities.push_back(entity);
}

void System::removeEntity(std::shared_ptr<Entity> entity) {
    entities.erase(std::remove(entities.begin(), entities.end(), entity), entities.end());
}

void System::clearEntities() {
    entities.clear();
}
