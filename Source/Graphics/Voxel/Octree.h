#pragma once
#include "../../Resource/Resource.h"
#include <json/json.hpp>

using json = nlohmann::json;

class Octree : public Resource {

public:
    Octree();
    void load(const std::string& path) override;
    void draw();

private:
    uint32_t* data;
    json source;
};
