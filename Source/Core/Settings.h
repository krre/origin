#pragma once
#include "Singleton.h"
#include <map>
#include <json/json.hpp>

using json = nlohmann::json;

class Settings : public Singleton<Settings> {

public:
    Settings();
    ~Settings();
    void setValue(const std::string& name, const std::string& value);
    std::string getValue(const std::string& name);
    void saveAll();

private:
    void setDefaultSettings();

    std::string path;
    json storage;
};
