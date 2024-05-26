#pragma once
#include "Core/SingleObject.h"
#include <json/json.hpp>

using json = nlohmann::json;

class Settings : public Core::SingleObject<Settings> {

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
