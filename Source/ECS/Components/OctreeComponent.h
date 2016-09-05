#pragma once
#include "../Component.h"
#include "../Graphics/Voxel/Octree.h"

class OctreeComponent : public Component {

public:
    OctreeComponent() { type = ComponentType::Octree; }
    uint32* data;
};
