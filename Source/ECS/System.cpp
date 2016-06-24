#include "System.h"

System::System() {

}

void System::addEntity(Entity* entity) {
    entities.push_back(entity);
}

void System::removeEntity(Entity* entity) {
    entities.remove(entity);
}

void System::clearEntities() {
    entities.clear();
}
