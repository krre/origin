#pragma once
#include "Singleton.h"
#include <map>

class Settings : public Singleton<Settings> {

public:
    Settings(const std::string& name);
    ~Settings();
    void setValue(const std::string& name, const std::string& value);
    std::string getValue(const std::string& name);
    void saveAll();

private:
    std::string path;
    std::map<std::string, std::string> storage;
};