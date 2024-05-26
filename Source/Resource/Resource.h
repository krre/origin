#pragma once
#include "Core/Object.h"

namespace Origin {

class Resource : public Core::Object {

public:
    Resource();
    virtual void load(const std::string& path) = 0;
};

} // Origin
