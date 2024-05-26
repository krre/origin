#include "OctreeSystem.h"

OctreeSystem::OctreeSystem(EntityManager* entityManager) : System(entityManager) {
    type = System::Type::Octree;
}

void OctreeSystem::process(float dt) {

}
