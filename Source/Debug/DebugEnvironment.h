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
    const getMainSettings() const { return mainSettings; }
    const getVulkanSettings() const { return vulkanSettings; }

private:
    void loadValues();
    bool enable = false;
    json mainSettings;
    json vulkanSettings;
};
