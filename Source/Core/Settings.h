#pragma once
#include "Singleton.h"

class Settings : public Singleton<Settings> {

public:
    Settings(const std::string& name);
    ~Settings();
    void saveAll();

private:
    std::string path;
};
