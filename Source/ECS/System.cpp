#include "System.h"
#include "EntityManager.h"
#include <algorithm>

EntityManager* System::entityManager;

System::System() {
    entityManager = EntityManager::get();
}

bool System::setActive(bool active) {
    this->active = active;
}
