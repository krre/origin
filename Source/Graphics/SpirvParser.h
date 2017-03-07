#pragma once
#include "../Core/Object.h"

#ifdef __linux__
#include <vulkan/libspirv.h>
#elif _WIN32
#include <spirv-tools/libspirv.h>
#endif

#include <map>

class SpirvParser : public Object {

public:

    struct Attributes {
        int descriptorSet;
        int location;
        int binding;
    };

    SpirvParser();
    ~SpirvParser();
    void parse(const uint32_t* code, size_t count);

private:
    spv_context context;
    std::map<std::string, Attributes> descriptors;
};
