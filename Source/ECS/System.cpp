#include "System.h"
#include "EntityManager.h"
#include <algorithm>

namespace Origin {

EntityManager* System::entityManager;

System::System() {
    entityManager = EntityManager::get();
}

void System::setActive(bool active) {
    this->active = active;
}

} // Origin
