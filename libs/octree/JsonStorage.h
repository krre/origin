#pragma once
#include <core/Object.h>
#include <json/json.hpp>

namespace Octree {

using json = nlohmann::json;

class JsonStorage : public Core::Object {
public:
    JsonStorage(Object* parent = nullptr);

private:
    json m_root;
};

}
