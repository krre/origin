#pragma once
#include "Common.h"

class Object {

public:
    Object();
    void setName(const std::string& name) { this->name = name; }
    const std::string& getName() const { return name; }

private:
    std::string name;
};
