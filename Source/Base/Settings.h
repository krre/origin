#pragma once
#include "Core/SingleObject.h"
#include <json/json.hpp>

namespace Origin {

using json = nlohmann::json;

class Settings : public SingleObject<Settings> {

public:
    Settings(Object* parent = nullptr);
    ~Settings();
    static void saveAll();
    static json& getStorage() { return get()->storage; }

private:
    void setDefaultSettings();

    std::string path;
    json storage;
};

} // Origin
