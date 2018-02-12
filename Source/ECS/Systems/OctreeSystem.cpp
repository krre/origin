#include "OctreeSystem.h"

namespace Origin {

OctreeSystem::OctreeSystem(EntityManager* entityManager) : System(entityManager) {
    type = System::Type::Octree;
}

void OctreeSystem::process(float dt) {

}

} // Origin
