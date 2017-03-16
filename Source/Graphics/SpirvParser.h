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

    struct Descriptor {
        int set;
        int location;
        int binding;
        VkDescriptorType descriptorType;
    };

    struct Input {
        int location;
        std::string shaderType;
        std::string variableType;
        std::string valueType;
        int vectorCount;
    };

    SpirvParser();
    ~SpirvParser();
    void parse(const uint32_t* code, size_t count);
    void dumpDescriptors();

    std::map<std::string, Input> inputs;
    std::map<std::string, Descriptor> descriptors;

private:
    spv_context context;
};
