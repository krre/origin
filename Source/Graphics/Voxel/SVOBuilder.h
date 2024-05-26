#pragma once
#include "Core/Object.h"
#include <vector>

class SVOBuilder : public Core::Object {

public:
    SVOBuilder();
    std::shared_ptr<std::vector<uint32_t>> buildTest();
};
