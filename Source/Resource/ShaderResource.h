#pragma once
#include "Resource.h"
#include <vector>
#include <map>
#include <vulkan/vulkan.h>

namespace Origin {

class ShaderResource : public Resource {

    friend class VulkanShaderProgram;

public:

    struct Location {
        int location;
        VkFormat format;
    };

    ShaderResource();
    void load(const std::string& path) override;
    VkShaderStageFlagBits getStage() const { return stage; }
    const uint32_t* getCodeData() const { return code.data(); }
    size_t getCodeSize() const { return code.size(); }

    void dumpBindings();
    void dumpLocations();

private:
    VkFormat getFormat(const std::string& variableType, const std::string& OpTypeFloat, int vectorCount = 0);

    VkShaderStageFlagBits stage;
    std::vector<uint32_t> code;
    std::map<std::string, Location> locations;
    std::map<std::string, VkDescriptorSetLayoutBinding> bindings;
    int set = 0;

    void parse();
};

} // Origin
