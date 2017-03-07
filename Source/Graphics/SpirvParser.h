#pragma once
#include "../Core/Object.h"

#ifdef __linux__
#include <vulkan/libspirv.h>
#elif _WIN32
#include <spirv-tools/libspirv.h>
#endif

#include <vector>

class SpirvParser : public Object {

public:

    struct Attributes {
        std::string name;
        int descriptorSet;
        int location;
        int binding;
    };

    SpirvParser();
    ~SpirvParser();
    void parse(const uint32_t* code, size_t count);

private:
    spv_context context;
    std::vector<Attributes> descriptors;
};
