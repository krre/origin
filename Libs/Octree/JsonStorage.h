#pragma once
#include "Core/Object.h"
#include <json/json.hpp>

namespace Core {

using json = nlohmann::json;

class JsonStorage : public Core::Object {

public:
    JsonStorage(Object* parent = nullptr);
    ~JsonStorage();

private:
    json root;
};

}
