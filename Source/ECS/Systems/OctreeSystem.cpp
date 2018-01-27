#include "OctreeSystem.h"

namespace Origin {

OctreeSystem::OctreeSystem(EntityManager* entityManager) : System(entityManager) {
    type = SystemType::Octree;
}

void OctreeSystem::process(float dt) {

}

} // Origin
