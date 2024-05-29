#include "System.h"
#include "EntityManager.h"

System::System(EntityManager* entityManager) : entityManager(entityManager) {
}

void System::setActive(bool active) {
    this->active = active;
}