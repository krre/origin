#pragma once
#include <core/Object.h>
#include <stdint.h>

class SVOBuilder : public Core::Object {
public:
    SVOBuilder();
    std::vector<uint32_t> buildTest();
};
