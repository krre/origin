#include "Shader.h"
#include <fstream>
#include <iostream>
#include <assert.h>

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
    spirv_cross::SPIREntryPoint& entryPoint = compiler.get_entry_point("main", compiler.get_execution_model());
    stage = executionModelToStage(entryPoint.model);

    spirv_cross::ShaderResources resources = compiler.get_shader_resources();
    std::vector<spirv_cross::SmallVector<spirv_cross::Resource>> resourcesList;
    resourcesList.push_back(resources.uniform_buffers);
    resourcesList.push_back(resources.storage_buffers);
    resourcesList.push_back(resources.stage_inputs);
    resourcesList.push_back(resources.stage_outputs);
    resourcesList.push_back(resources.subpass_inputs);
    resourcesList.push_back(resources.storage_images);
    resourcesList.push_back(resources.sampled_images);
    resourcesList.push_back(resources.atomic_counters);
    resourcesList.push_back(resources.push_constant_buffers);
    resourcesList.push_back(resources.separate_images);
    resourcesList.push_back(resources.separate_samplers);

    for (const auto& resource : resourcesList) {
        for (const auto& buffer : resource) {
            BufferInfo bufferInfo;
            bufferInfo.typeName = buffer.name;
            bufferInfo.variableName = compiler.get_name(buffer.id);
            bufferInfo.set = compiler.get_decoration(buffer.id, spv::DecorationDescriptorSet);
            bufferInfo.layoutBinding.stageFlags = stage;
            bufferInfo.layoutBinding.binding = compiler.get_decoration(buffer.id, spv::DecorationBinding);
            bufferInfo.layoutBinding.descriptorType = VK_DESCRIPTOR_TYPE_MAX_ENUM;
            bufferInfo.layoutBinding.descriptorCount = 1;
            bufferInfo.layoutBinding.pImmutableSamplers = NULL;

            spv::StorageClass storageClass = compiler.get_storage_class(buffer.id);
            spirv_cross::SPIRType type = compiler.get_type_from_variable(buffer.id);
            spirv_cross::Bitset decorationBitset = compiler.get_decoration_bitset(buffer.base_type_id);

            if (storageClass == spv::StorageClassOutput) {
                continue;
            } else if (storageClass == spv::StorageClassInput) {
                if (stage == VK_SHADER_STAGE_VERTEX_BIT) {
                    // Location
                    LocationInfo locationInfo;
                    locationInfo.name = buffer.name;
                    locationInfo.location = compiler.get_decoration(buffer.id, spv::DecorationLocation);
                    locationInfo.format = spirvTypeToFormat(type);
                    locations.push_back(locationInfo);
                }
                continue;
            } else if (storageClass == spv::StorageClassUniformConstant) {
                if (type.basetype == spirv_cross::SPIRType::Image) {
                    if (type.image.dim == spv::DimBuffer) {
                        bufferInfo.layoutBinding.descriptorType = VK_DESCRIPTOR_TYPE_STORAGE_TEXEL_BUFFER;
                    } else {
                        if (type.image.format == spv::ImageFormat::ImageFormatUnknown) {
                            bufferInfo.layoutBinding.descriptorType = VK_DESCRIPTOR_TYPE_SAMPLED_IMAGE;
                        } else {
                            bufferInfo.layoutBinding.descriptorType = VK_DESCRIPTOR_TYPE_STORAGE_IMAGE;
                        }
                    }
                } else if (type.basetype == spirv_cross::SPIRType::Sampler) {
                    bufferInfo.layoutBinding.descriptorType = VK_DESCRIPTOR_TYPE_SAMPLER;
                } else if (type.basetype == spirv_cross::SPIRType::SampledImage) {
                    if (type.image.dim == spv::DimBuffer) {
                        bufferInfo.layoutBinding.descriptorType = VK_DESCRIPTOR_TYPE_UNIFORM_TEXEL_BUFFER;
                    } else {
                        bufferInfo.layoutBinding.descriptorType = VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER;
                    }
                }

                if (type.array.size()) {
                    bufferInfo.layoutBinding.descriptorCount = type.array[0];
                }
            } else if (storageClass == spv::StorageClassUniform && decorationBitset.get(spv::DecorationBlock)) {
                bufferInfo.layoutBinding.descriptorType = VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER;
            } else if (storageClass == spv::StorageClassUniform && decorationBitset.get(spv::DecorationBufferBlock)) {
                bufferInfo.layoutBinding.descriptorType = VK_DESCRIPTOR_TYPE_STORAGE_BUFFER;
            } else if (storageClass == spv::StorageClassStorageBuffer) {
                bufferInfo.layoutBinding.descriptorType = VK_DESCRIPTOR_TYPE_STORAGE_BUFFER;
            }

            assert(bufferInfo.layoutBinding.descriptorType != VK_DESCRIPTOR_TYPE_MAX_ENUM);

            bindings.push_back(bufferInfo);
        }
    }

#if 0
    dumpBindings();
    dumpLocations();
#endif
}

void Shader::dumpBindings() {
    std::cout << "Dump SPIR-V bindings (stage " << stage << "):" << std::endl;
    for (const auto& binding : bindings) {
        std::cout << "type name: " << binding.typeName
            << ", variable name: " << binding.variableName
            << ", set: " << binding.set
            << ", binding: " << binding.layoutBinding.binding
            << ", descriptorType: " << binding.layoutBinding.descriptorType
            << ", descriptorCount: " << binding.layoutBinding.descriptorCount
            << std::endl;
    }
}

void Shader::dumpLocations() {
    std::cout << "Dump SPIR-V locations (stage " << stage << "):" << std::endl;
    for (const auto& location : locations) {
        std::cout << "name: " << location.name
            << ", location: " << location.location
            << ", format: " << location.format
            << std::endl;
    }
}

VkShaderStageFlagBits Shader::executionModelToStage(spv::ExecutionModel model) {
    switch (model) {
        case spv::ExecutionModelVertex: return VK_SHADER_STAGE_VERTEX_BIT;
        case spv::ExecutionModelTessellationControl: return VK_SHADER_STAGE_TESSELLATION_CONTROL_BIT;
        case spv::ExecutionModelTessellationEvaluation: return VK_SHADER_STAGE_TESSELLATION_EVALUATION_BIT;
        case spv::ExecutionModelGeometry: return VK_SHADER_STAGE_GEOMETRY_BIT;
        case spv::ExecutionModelFragment: return VK_SHADER_STAGE_FRAGMENT_BIT;
        case spv::ExecutionModelGLCompute: return VK_SHADER_STAGE_COMPUTE_BIT;
        default: break;
    }

    assert(false);
    return VK_SHADER_STAGE_FLAG_BITS_MAX_ENUM;
}

VkFormat Shader::spirvTypeToFormat(spirv_cross::SPIRType type) {
    if (type.basetype == spirv_cross::SPIRType::Float) {
        if (type.vecsize == 2) {
            return VK_FORMAT_R32G32_SFLOAT;
        } else if (type.vecsize == 3) {
            return VK_FORMAT_R32G32B32_SFLOAT;
        } else if (type.vecsize == 4) {
            return VK_FORMAT_R32G32B32A32_SFLOAT;
        }
    }

    assert(false);
    return VK_FORMAT_MAX_ENUM;
}

}
