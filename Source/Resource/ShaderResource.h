#pragma once
#include "Resource.h"
#include <vector>
#include <map>
#include <vulkan/vulkan.h>

#ifdef __linux__
#include <vulkan/libspirv.h>
#elif _WIN32
#include <spirv-tools/libspirv.h>
#endif

class ShaderResource : public Resource {

public:

    struct Descriptor {
        int set;
        int location;
        int binding;
        VkDescriptorType descriptorType;
    };

    struct Input {
        int location;
        std::string variableType;
        std::string valueType;
        int vectorCount;
    };

    ShaderResource();
    ~ShaderResource();
    void load(const std::string& path) override;
    const uint32_t* getData() const { return buffer.data(); }
    size_t getSize() const { return buffer.size(); }

    void dumpDescriptors();
    void dumpInputs();

private:
    spv_context context;
    std::vector<uint32_t> buffer;
    std::map<std::string, Input> inputs;
    std::map<std::string, Descriptor> descriptors;

    void parse(const uint32_t* code, size_t count);
};
