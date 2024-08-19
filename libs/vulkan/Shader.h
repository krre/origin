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

    void load(const std::string& filePath);

    VkShaderStageFlagBits stage() const { return m_stage; }
    const std::vector<uint32_t>& code() const { return m_code; }

    const std::vector<BufferInfo> bindings() const { return m_bindings; }
    const std::vector<LocationInfo> locations() const { return m_locations; }

    void dumpBindings();
    void dumpLocations();

private:
    void parse();
    VkShaderStageFlagBits executionModelToStage(spv::ExecutionModel model);
    VkFormat spirvTypeToFormat(spirv_cross::SPIRType type);

    std::vector<uint32_t> m_code;
    VkShaderStageFlagBits m_stage;
    std::vector<BufferInfo> m_bindings;
    std::vector<LocationInfo> m_locations;
};

}
