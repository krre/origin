#pragma once
#include "../Core/Object.h"

class Resource : public Object {

public:
    Resource();
    virtual void load(const std::string& path) {}
    virtual void load() {}
    virtual void release() {}
};
