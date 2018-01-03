#pragma once
#include "Core/Object.h"

namespace Origin {

class Resource : public Object {

public:
    Resource();
    virtual void load(const std::string& path) {}
};

} // Origin
