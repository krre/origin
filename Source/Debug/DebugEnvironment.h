#pragma once
#include "Core/Object.h"
#include <json/json.hpp>

namespace Origin {

using json = nlohmann::json;

class DebugEnvironment : public Object {

public:
    DebugEnvironment(Object* parent = nullptr);
    bool getEnable() const { return enable; }
    void setDebugScreen();
    json& getSettings() { return settings; }
    int getVulkanDevice() { return settings["vulkan"]["device"]; }

private:
    void loadValues();
    bool enable = false;
    json settings;
};

} // Origin
