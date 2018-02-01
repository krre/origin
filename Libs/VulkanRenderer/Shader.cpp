#include "Shader.h"
#include <fstream>
#include <spirv_cross/spirv_cross.hpp>

namespace Vulkan {

Shader::Shader() {

}

Shader::~Shader() {

}

void Shader::load(const std::string& filePath) {
    std::ifstream file(filePath, std::ios::ate | std::ios::binary);

    if (!file.is_open()) {
        throw std::runtime_error("Failed to open file: " + filePath);
    }

    size_t fileSize = (size_t)file.tellg();
    code.resize(fileSize / sizeof(uint32_t));

    file.seekg(0);
    file.read(reinterpret_cast<char*>(code.data()), fileSize);
    file.close();

    if (!code.empty()) {
        analyze();
    }
}

void Shader::analyze() {
    spirv_cross::Compiler compiler(code);
    spirv_cross::ShaderResources resources = compiler.get_shader_resources();
    for (auto &u : resources.uniform_buffers) {
        uint32_t set = compiler.get_decoration(u.id, spv::DecorationDescriptorSet);
        uint32_t binding = compiler.get_decoration(u.id, spv::DecorationBinding);
        printf("Found UBO %s at set = %u, binding = %u!\n", u.name.c_str(), set, binding);
    }
}

} // Origin
