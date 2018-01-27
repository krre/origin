#include "System.h"
#include "EntityManager.h"
#include <algorithm>

namespace Origin {

System::System(EntityManager* entityManager) : entityManager(entityManager) {
}

void System::setActive(bool active) {
    this->active = active;
}

} // Origin
