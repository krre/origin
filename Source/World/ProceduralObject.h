#pragma once
#include "Core/Object.h"
#include <vector>

namespace Origin {

class ProceduralObject : public Core::Object {

public:
    ProceduralObject();
    virtual void make() = 0;

private:
    uint64_t seed;
    std::shared_ptr<std::vector<uint32_t>> data;
};

} // Origin
