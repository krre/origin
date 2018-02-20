#pragma once
#include "ECS/Component.h"
#include "Octree/Octree.h"
#include <vector>

namespace Origin {

class OctreeComponent : public Component {

public:
    OctreeComponent() { type = Component::Type::Octree; }
    std::shared_ptr<std::vector<uint32_t>> data;
};

} // Origin
