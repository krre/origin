#pragma once
#include "../Core/Object.h"

#ifdef __linux__
#include <vulkan/libspirv.h>
#elif _WIN32
#include <spirv-tools/libspirv.h>
#endif

#include <vector>
#include <vulkan/vulkan.h>

class SpirvParser : public Object {

public:

    struct Descriptor {
        std::string name;
        int set;
        int location;
        int binding;
        VkDescriptorType descriptorType;
        std::string variableType;
    };

    SpirvParser();
    ~SpirvParser();
    void parse(const uint32_t* code, size_t count);
    void dumpDescriptors();

    std::vector<Descriptor> descriptors;

private:
    spv_context context;
};
