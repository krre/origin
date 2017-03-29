#pragma once
#include "Resource.h"
#include <vector>
#include <map>
#include <vulkan/vulkan.h>

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
    void load(const std::string& path) override;
    const uint32_t* getCodeData() const { return code.data(); }
    size_t getCodeSize() const { return code.size(); }

    void dumpDescriptors();
    void dumpInputs();

private:
    std::vector<uint32_t> code;
    std::map<std::string, Input> inputs;
    std::map<std::string, Descriptor> descriptors;

    void parse();
};
