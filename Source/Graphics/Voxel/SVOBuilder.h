#pragma once
#include "Core/Object.h"
#include <vector>

namespace Origin {

class SVOBuilder : public Object {

public:
    SVOBuilder();
    std::shared_ptr<std::vector<uint32_t>> buildTest();
};

} // Origin
