#pragma once
#include "Core/Object.h"

namespace Origin {

class Octree;

class Scene : public Object {

public:
    Scene(Object* parent = nullptr);
    ~Scene();

    void addOctree(Octree* octree);
    Object* getRootOctree() const { return rootOctree; }

private:
    Object* rootOctree;
};

} // Origin
