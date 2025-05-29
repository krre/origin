#pragma once
#include <core/Object.h>
#include <memory>

class SVOBuilder : public Core::Object {
public:
    SVOBuilder();
    std::shared_ptr<std::vector<uint32_t>> buildTest();
};
