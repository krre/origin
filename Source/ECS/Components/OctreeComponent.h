#pragma once
#include "ECS/Component.h"
#include "Octree/Octree.h"

namespace Origin {

class OctreeComponent : public Component {

public:
    OctreeComponent() = default;
    Type getType() const override { return Component::Type::Octree; }

    std::shared_ptr<Core::Octree> octree;
};

} // Origin
