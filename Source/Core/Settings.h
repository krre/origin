#pragma once
#include <json/json.hpp>

namespace Origin {

using json = nlohmann::json;

class Settings {

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

} // Origin
