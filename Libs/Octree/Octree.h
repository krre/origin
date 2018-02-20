#pragma once
#include "Core/Object.h"

namespace Origin {

class JsonStorage;

class Octree : public Object {

public:
    Octree(Object* parent = nullptr);
    ~Octree();

    void load(const std::string& path);

private:
    JsonStorage* storage;
};

} // Origin
