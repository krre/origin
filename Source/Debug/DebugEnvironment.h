#pragma once
#include "Core/Singleton.h"
#include "Graphics/GraphicsTypes.h"
#include <json/json.hpp>

namespace Origin {

using json = nlohmann::json;

class DebugEnvironment : public Singleton<DebugEnvironment> {

public:
    DebugEnvironment();
    bool getEnable() const { return enable; }
    void setDebugScreen();
    json& getSettings() { return settings; }

private:
    void loadValues();
    bool enable = false;
    json settings;
};

} // Origin
