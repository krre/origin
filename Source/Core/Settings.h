#pragma once
#include "Singleton.h"
#include <json/json.hpp>

using json = nlohmann::json;

class Settings : public Singleton<Settings> {

public:
    Settings();
    ~Settings();
    void saveAll();
    json& getStorage() { return storage; }

private:
    void setDefaultSettings();

    std::string path;
    json storage;
};
