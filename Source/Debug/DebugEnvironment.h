#pragma once
#include "Core/Singleton.h"
#include <json/json.hpp>

using json = nlohmann::json;

class DebugEnvironment : public Singleton<DebugEnvironment> {

public:
    DebugEnvironment();
    bool getEnable() const { return enable; }
    void setDebugScreen();
    json& getMain() { return mainSettings; }
    json& getVulkan() { return vulkanSettings; }

private:
    void loadValues();
    bool enable = false;
    json mainSettings;
    json vulkanSettings;
};
