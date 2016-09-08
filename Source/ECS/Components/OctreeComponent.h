#pragma once
#include "../Component.h"
#include "../Graphics/Voxel/Octree.h"
#include <vector>

class OctreeComponent : public Component {

public:
    OctreeComponent() { type = ComponentType::Octree; }
    std::vector<uint32> data;
};
