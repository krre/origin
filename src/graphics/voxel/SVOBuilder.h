#pragma once
#include <core/Object.h>

class SVOBuilder : public Core::Object {
public:
    SVOBuilder();
    std::vector<uint32_t> buildTest();
};
