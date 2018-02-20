#pragma once
#include "ECS/Component.h"
#include "Octree/Octree.h"

namespace Origin {

class OctreeComponent : public Component {

public:
    OctreeComponent() { type = Component::Type::Octree; }
    std::shared_ptr<Octree> octree;
};

} // Origin
