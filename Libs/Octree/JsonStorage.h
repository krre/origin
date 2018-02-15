#pragma once
#include "Core/Object.h"
#include <json/json.hpp>

namespace Origin {

using json = nlohmann::json;

class JsonStorage : public Object {

public:
    JsonStorage(Object* parent = nullptr);
    ~JsonStorage();

    void create();

private:
    json root;
};

} // Origin
