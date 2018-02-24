#pragma once
#include "Core/Object.h"

namespace Origin {

class Substance : public Object {

public:
    Substance();
    ~Substance();

private:
    uint32_t substance = 0;

};

} // Origin
