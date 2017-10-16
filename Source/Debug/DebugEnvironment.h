#pragma once
#include "Core/Singleton.h"
#include <map>

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
    std::map<std::string, std::string> values;
};
