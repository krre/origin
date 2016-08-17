#pragma once
#include "../Component.h"
#include "../Graphics/Voxel/Octree.h"

class OctreeComponent : public Component {

public:
    OctreeComponent() { type = ComponentType::Octree; }
    std::shared_ptr<Octree> octree;
    float size = 1.0;
};
