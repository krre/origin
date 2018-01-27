#include "System.h"
#include "EntityManager.h"
#include <algorithm>

namespace Origin {

System::System() {
}

void System::setActive(bool active) {
    this->active = active;
}

void System::setEntityManager(EntityManager* entityManager) {
    this->entityManager = entityManager;
}

} // Origin
