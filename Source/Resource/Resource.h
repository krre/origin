#pragma once
#include "../Core/Object.h"

class Resource : public Object {

public:
    Resource();
    virtual void load(std::string path) = 0;
    virtual void release() = 0;
};
