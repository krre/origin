#pragma once
#include "../Core/Singleton.h"
#include <map>

class Debug : public Singleton<Debug> {

public:
    Debug();
    void setValue(const std::string& key, const std::string& value);
    std::string getValue(const std::string& key) const;
    bool getEnable() const { return enable; }
    void setDebugScene();

private:
    void loadValues();
    bool enable = false;
    std::map<std::string, std::string> values;
};
