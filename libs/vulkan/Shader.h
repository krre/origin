#pragma once
#include <vector>
#include <string>
#include <vulkan/vulkan.h>
#include <spirv_cross/spirv_cross.hpp>

namespace Vulkan {

class Shader {

public:
    struct BufferInfo {
        std::string typeName;
        std::string variableName;
        uint32_t set;
        VkDescriptorSetLayoutBinding layoutBinding;
    };

    struct LocationInfo {
        std::string name;
        uint32_t location;
        VkFormat format;
    };

    Shader();
    ~Shader();
    void load(const std::string& filePath);

    VkShaderStageFlagBits getStage() const { return stage; }
    const std::vector<uint32_t>& getCode() const { return code; }

    const std::vector<BufferInfo> getBindings() const { return bindings; }
    const std::vector<LocationInfo> getLocations() const { return locations; }

    void dumpBindings();
    void dumpLocations();

private:
    void parse();
    VkShaderStageFlagBits executionModelToStage(spv::ExecutionModel model);
    VkFormat spirvTypeToFormat(spirv_cross::SPIRType type);

    std::vector<uint32_t> code;
    VkShaderStageFlagBits stage;
    std::vector<BufferInfo> bindings;
    std::vector<LocationInfo> locations;
};

}
