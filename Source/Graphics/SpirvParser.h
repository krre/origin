#pragma once
#include "../Core/Object.h"
#include <vulkan/libspirv.h>

class SpirvParser : public Object {

public:
    SpirvParser();
    ~SpirvParser();
    void parse(const uint32_t* code, size_t count);

private:
    spv_context context;
};
