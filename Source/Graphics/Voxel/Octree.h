#pragma once
#include "Resource/Resource.h"
#include <json/json.hpp>

namespace Origin {

using json = nlohmann::json;

class Octree : public Resource {

public:
    Octree();
    void load(const std::string& path) override;
    void draw();
    std::shared_ptr<std::vector<uint32_t>> data();

private:
    json source;
};

} // Origin
