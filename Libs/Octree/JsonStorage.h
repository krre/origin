#pragma once
#include <json/json.hpp>

namespace Octree {

using json = nlohmann::json;

class JsonStorage {

public:
    JsonStorage();
    ~JsonStorage();

    void create();

private:
    json root;
};

} // Octree
