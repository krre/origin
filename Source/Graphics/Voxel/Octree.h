#pragma once
#include "../../Resource/Resource.h"

class Octree : public Resource {

public:
    Octree();
    void load(const std::string& path) override;
    void draw();

private:
    uint32_t* data;
};
