#pragma once
#include "../../Core/Object.h"

class Octree : public Object {

public:
    Octree();
    void draw();

private:
    uint32_t* data;
};
