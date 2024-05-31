#include "OctreeSystem.h"

OctreeSystem::OctreeSystem(EntityManager* entityManager) : System(entityManager) {
    m_type = System::Type::Octree;
}

void OctreeSystem::process(float dt) {

}
