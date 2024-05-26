#pragma once
#include "Core/Object.h"

namespace Core {

class Substance : public Core::Object {

public:
    Substance();
    ~Substance();
    uint32_t getId() const { return id; }

private:
    uint32_t id = 0;

};

}
