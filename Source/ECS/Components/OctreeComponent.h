#pragma once
#include "ECS/Component.h"
#include "Graphics/Voxel/Octree.h"
#include <vector>

namespace Origin {

class OctreeComponent : public Component {

public:
    OctreeComponent() { type = ComponentType::Octree; }
    std::shared_ptr<std::vector<uint32_t>> data;
};

} // Origin
