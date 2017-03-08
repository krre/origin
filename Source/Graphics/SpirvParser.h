#pragma once
#include "../Core/Object.h"

#ifdef __linux__
#include <vulkan/libspirv.h>
#elif _WIN32
#include <spirv-tools/libspirv.h>
#endif

#include <map>
#include <vulkan/vulkan.h>

class SpirvParser : public Object {

public:

    struct Attributes {
        std::string name;
        int descriptorSet;
        int location;
        int binding;
        VkDescriptorType type;
    };

    SpirvParser();
    ~SpirvParser();
    void parse(const uint32_t* code, size_t count);
    void dumpDescriptors();

    std::map<std::string, Attributes> descriptors;

private:
    spv_context context;
};
