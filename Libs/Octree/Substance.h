#pragma once
#include "Core/Object.h"

namespace Origin {

class Substance : public Object {

public:
    Substance();
    ~Substance();
    uint32_t getId() const { return id; }

private:
    uint32_t id = 0;

};

} // Origin
