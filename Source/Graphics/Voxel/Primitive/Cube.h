#pragma once
#include "Octree/Octree.h"

namespace Origin {

class Cube : public Octree::Octree {

public:
    Cube(float width = 1.0, float height = 1.0, float depth = 1.0);

private:
    float width;
    float height;
    float depth;
};

} // Origin
