#pragma once
#include "Core/Singleton.h"
#include "Graphics/GraphicsTypes.h"
#include <json/json.hpp>

using json = nlohmann::json;

class DebugEnvironment : public Singleton<DebugEnvironment> {

public:
    DebugEnvironment();
    bool getEnable() const { return enable; }
    GraphicsBackend getGraphicsBackend() const;
    void setDebugScreen();
    json& getSettings() { return settings; }

private:
    void loadValues();
    bool enable = false;
    json settings;
};
