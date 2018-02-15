#pragma once
#include "Core/Object.h"
#include <json/json.hpp>

namespace Origin {

using json = nlohmann::json;

class Settings : public Object {

public:
    Settings(Object* parent = nullptr);
    ~Settings();
    void saveAll();
    json& getStorage() { return storage; }

private:
    void setDefaultSettings();

    std::string path;
    json storage;
};

} // Origin
