#pragma once
#include <core/Object.h>

class Resource : public Core::Object {

public:
    Resource();
    virtual void load(const std::string& path) = 0;
};
