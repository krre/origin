#pragma once
#include "../../Resource/Resource.h"

class Octree : public Resource {

public:
    Octree();
    void draw();

private:
    uint32_t* data;
};
