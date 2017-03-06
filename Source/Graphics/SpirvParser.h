#pragma once
#include "../Core/Object.h"
#ifdef __linux__
#include <vulkan/libspirv.h>
#elif _WIN32
#include <spirv-tools/libspirv.h>
#endif

class SpirvParser : public Object {

public:
    SpirvParser();
    ~SpirvParser();
    void parse(const uint32_t* code, size_t count);

private:
    spv_context context;
};
