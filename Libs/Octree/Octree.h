#pragma once
#include "Core/Object.h"

namespace Origin {

class JsonStorage;

class Octree : public Object {

public:
    Octree(Object* parent = nullptr);
    ~Octree();

private:
    JsonStorage* storage;
};

} // Origin
