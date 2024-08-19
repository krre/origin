#include "System.h"
#include "EntityManager.h"

System::System(EntityManager* entityManager) : m_entityManager(entityManager) {
}

void System::setActive(bool active) {
    m_active = active;
}
