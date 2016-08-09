#pragma once
#include "../Component.h"
#include "../Graphics/Mesh.h"

class OctreeComponent : public Component {

public:
    OctreeComponent() { type = ComponentType::Octree; }
};
