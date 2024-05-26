#include "System.h"
#include "EntityManager.h"
#include <algorithm>

System::System(EntityManager* entityManager) : entityManager(entityManager) {
}

void System::setActive(bool active) {
    this->active = active;
}
