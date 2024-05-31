#pragma once
#include "ecs/Component.h"
#include <octree/Octree.h>

class OctreeComponent : public Component {

public:
    OctreeComponent() = default;
    Type type() const override { return Component::Type::Octree; }

    std::shared_ptr<Octree::Octree> octree;
};
