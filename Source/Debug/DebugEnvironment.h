#pragma once
#include "Core/Singleton.h"
#include <json/json.hpp>

using json = nlohmann::json;

class DebugEnvironment : public Singleton<DebugEnvironment> {

public:
    DebugEnvironment();
    void setValue(const std::string& key, const std::string& value);
    std::string getValue(const std::string& key) const;
    bool getEnable() const { return enable; }
    void setDebugScreen();

private:
    void loadValues();
    bool enable = false;
    json mainStorage;
    json vulkanStorage;
};
