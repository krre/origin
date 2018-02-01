#include "Shader.h"
#include <fstream>
#include <iostream>

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
        parse();
    }
}

void Shader::parse() {
    spirv_cross::Compiler compiler(code);

    // Stage flag
    spirv_cross::SPIREntryPoint entryPoint = compiler.get_entry_point("main");
    stage = getStage(entryPoint.model);
//    std::cout << stage << std::endl;

//    spirv_cross::ShaderResources resources = compiler.get_shader_resources();
//    for (auto &u : resources.uniform_buffers) {
//        uint32_t set = compiler.get_decoration(u.id, spv::DecorationDescriptorSet);
//        uint32_t binding = compiler.get_decoration(u.id, spv::DecorationBinding);
//        printf("Found UBO %s at set = %u, binding = %u!\n", u.name.c_str(), set, binding);
//    }


}

VkShaderStageFlagBits Shader::getStage(spv::ExecutionModel model) {
    switch (model) {
        case spv::ExecutionModel::ExecutionModelVertex: return VK_SHADER_STAGE_VERTEX_BIT;
        case spv::ExecutionModel::ExecutionModelTessellationControl: return VK_SHADER_STAGE_TESSELLATION_CONTROL_BIT;
        case spv::ExecutionModel::ExecutionModelTessellationEvaluation: return VK_SHADER_STAGE_TESSELLATION_EVALUATION_BIT;
        case spv::ExecutionModel::ExecutionModelGeometry: return VK_SHADER_STAGE_GEOMETRY_BIT;
        case spv::ExecutionModel::ExecutionModelFragment: return VK_SHADER_STAGE_FRAGMENT_BIT;
        case spv::ExecutionModel::ExecutionModelGLCompute: return VK_SHADER_STAGE_COMPUTE_BIT;
        default: break;
    }

    return VK_SHADER_STAGE_FLAG_BITS_MAX_ENUM;
}

} // Vulkan
