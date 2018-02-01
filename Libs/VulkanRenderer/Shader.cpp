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
    spirv_cross::SPIREntryPoint& entryPoint = compiler.get_entry_point("main");
    stage = getStage(entryPoint.model);
//    std::cout << stage << std::endl;

    spirv_cross::ShaderResources resources = compiler.get_shader_resources();

    std::vector<BufferInfo> infos;

    // Uniform
    for (auto& buffer : resources.uniform_buffers) {
        BufferInfo bufferInfo;
        bufferInfo.name = buffer.name;
        bufferInfo.set = compiler.get_decoration(buffer.id, spv::DecorationDescriptorSet);
        bufferInfo.binding = compiler.get_decoration(buffer.id, spv::DecorationBinding);
        bufferInfo.type = VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER;
        infos.push_back(bufferInfo);
    }

    // Storage
    for (auto& buffer : resources.storage_buffers) {
        BufferInfo bufferInfo;
        bufferInfo.name = buffer.name;
        bufferInfo.set = compiler.get_decoration(buffer.id, spv::DecorationDescriptorSet);
        bufferInfo.binding = compiler.get_decoration(buffer.id, spv::DecorationBinding);
        bufferInfo.type = VK_DESCRIPTOR_TYPE_STORAGE_BUFFER;
        infos.push_back(bufferInfo);
    }
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
