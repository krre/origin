#include "System.h"
#include <algorithm>

System::System() {

}

void System::addEntity(Entity* entity) {
    entities.push_back(entity);
}

void System::removeEntity(Entity* entity) {
    entities.erase(std::remove(entities.begin(), entities.end(), entity), entities.end());
}

void System::clearEntities() {
    entities.clear();
}
