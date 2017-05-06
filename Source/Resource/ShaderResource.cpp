#include "ShaderResource.h"
#include <fstream>
#include "Core/Utils.h"
#include <assert.h>

#ifdef __linux__
#include <vulkan/libspirv.h>
#elif _WIN32
#include <spirv-tools/libspirv.h>
#endif

ShaderResource::ShaderResource() {
}

void ShaderResource::load(const std::string& path) {
    std::ifstream file(path, std::ios::ate | std::ios::binary);

    if (!file.is_open()) {
        throw std::runtime_error("Failed to open file: " + path);
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

VkFormat ShaderResource::getFormat(const std::string& variableType, const std::string& valueType, int vectorCount) {
    if (variableType == "OpTypeVector") {
        if (valueType == "OpTypeFloat") {
            if (vectorCount == 2) {
                return VK_FORMAT_R32G32_SFLOAT;
            } else if (vectorCount == 3) {
                return VK_FORMAT_R32G32B32_SFLOAT;
            }
        }
    }

    assert(0);
}

void ShaderResource::parse() {
    assert(bindings.empty());
    assert(locations.empty());

    spv_context context = spvContextCreate(SPV_ENV_UNIVERSAL_1_0);
    spv_diagnostic diagnostic = nullptr;
    spv_text resultText = nullptr;
    spvBinaryToText(context, code.data(), code.size(), 0, &resultText, &diagnostic);
    if (diagnostic) {
        spvDiagnosticPrint(diagnostic);
        spvDiagnosticDestroy(diagnostic);
        assert(false);
    }

//    PRINT(resultText->str)
//    PRINT("================")

    std::string shaderType;
    std::map<std::string, std::string> names;
    std::map<std::string, std::vector<std::string>> instructions;
    std::vector<std::string> line;
    std::string word;
    VkDescriptorType blockType;

    // Parse SPIR-V text code to vector of lines
    int i = 0;
    const char quote = '\"';
    while (i < resultText->length) {
        char c = resultText->str[i++];
        if (c == ' ') {
            line.push_back(word);
            word.clear();
            continue;
        }

        if (c == '\n') {
            line.push_back(word);
            std::string& firstWord = line.at(0);
            if (firstWord == "OpEntryPoint") {
                shaderType = line.at(1);
                if (shaderType == "Vertex") {
                    stage = VK_SHADER_STAGE_VERTEX_BIT;
                } else if (shaderType == "Fragment") {
                    stage = VK_SHADER_STAGE_FRAGMENT_BIT;
                } else if (shaderType == "GLCompute") {
                    stage = VK_SHADER_STAGE_COMPUTE_BIT;
                } else {
                    assert(0 && "Unknown shader type");
                }
            } else if (firstWord == "OpName") {
                // Example:
                // OpName %44 "ubo"
                Utils::removeChar(line.at(2), quote);
                names[line.at(1)] = line.at(2);
            } else if (firstWord == "OpDecorate") {
                // Set descriptor for uniform buffers and storage buffers
                // Example:
                // OpDecorate %83 Block|BufferBlock
                // OpDecorate %85 DescriptorSet 0
                // OpDecorate %85 Binding 1
                std::string& id = line.at(1);
                std::string& decorateName = line.at(2);

                if (decorateName == "Block") {
                    blockType = VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER;
                } else if (decorateName == "BufferBlock") {
                    blockType = VK_DESCRIPTOR_TYPE_STORAGE_BUFFER;
                } else if (decorateName == "DescriptorSet") {
                    std::string& name = names.at(id);
                    bindings[name] = {};
//                    bindings.at(name).set = std::stoi(line.at(3));
                    bindings.at(name).descriptorType = blockType; // from previous line of SPIR-V code
                    bindings.at(name).stageFlags = stage;
                } else if (decorateName == "Binding") {
                    std::string& name = names.at(id);
                    bindings.at(name).binding = std::stoi(line.at(3));
                } else if (decorateName == "Location" && shaderType == "Vertex") {
                    std::string& name = names.at(id);
                    locations[name] = {};
                    locations.at(name).location = std::stoi(line.at(3));
                }
            } else if (firstWord.at(0) == '%') {
                std::string& id = firstWord;
                // Set descriptor for uniforms, samplers and texel buffers
                // Example:
                // %9 = OpTypeImage %6 2D 0 0 0 1 Unknown
                // %10 = OpTypeSampledImage %9
                // %11 = OpTypePointer UniformConstant %10
                // %12 = OpVariable %11 UniformConstant
                if (line.at(2) == "OpVariable") {
                    std::string& name = names.at(id);
                    std::string& storageClass = line.at(4);
                    std::string& typeId = instructions.at(line.at(3)).at(4);
                    std::string& type = instructions.at(typeId).at(2);

                    uint32_t descriptorCount = 1;
                    // Find count of array elements.
                    // Example:
                    // %24 = OpConstant %14 13
                    // %25 = OpTypeArray %23 %24
                    // %26 = OpTypePointer Uniform %25
                    // %27 = OpVariable %26 Uniform
                    if (type == "OpTypeArray") {
                        std::string& lengthId = instructions.at(typeId).at(4);
                        descriptorCount = std::stoi(instructions.at(lengthId).at(4));
                    }

                    if (bindings.find(name) != bindings.end()) {
                        bindings.at(name).descriptorCount = descriptorCount;
                    }

                    if (storageClass == "UniformConstant") {
                        if (type == "OpTypeImage") {
                            if (instructions.at(typeId).at(4) == "Buffer") {
                                bindings.at(name).descriptorType = VK_DESCRIPTOR_TYPE_STORAGE_TEXEL_BUFFER;
                            } else {
                                if (instructions.at(typeId).at(9) == "Unknown") {
                                    bindings.at(name).descriptorType = VK_DESCRIPTOR_TYPE_SAMPLED_IMAGE;
                                } else {
                                    bindings.at(name).descriptorType = VK_DESCRIPTOR_TYPE_STORAGE_IMAGE;
                                }
                            }
                        } else if (type == "OpTypeSampler") {
                            bindings.at(name).descriptorType = VK_DESCRIPTOR_TYPE_SAMPLER;
                        } else if (type == "OpTypeSampledImage") {
                            std::string& typeId2 = instructions.at(typeId).at(3);
                            std::string& type2 = instructions.at(typeId2).at(4);
                            if (type2 == "Buffer") {
                                bindings.at(name).descriptorType = VK_DESCRIPTOR_TYPE_UNIFORM_TEXEL_BUFFER;
                            } else {
                                bindings.at(name).descriptorType = VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER;
                            }
                        }
                    } else if (storageClass == "Uniform") {
                        // TODO: Add code
                    } else if (storageClass == "PushConstant") {
                        // TODO: Add code
                    } else if (storageClass == "Input" && shaderType == "Vertex") {
                        if (locations.find(name) != locations.end()) {
                            if (type == "OpTypeVector") {
                                int vectorCount = std::stoi(instructions.at(typeId).at(4));
                                std::string& vectorTypeId = instructions.at(typeId).at(3);
                                std::string valueType = instructions.at(vectorTypeId).at(2);
                                locations.at(name).format = getFormat(type, valueType, vectorCount);
                            }
                        }
                    }
                }
                instructions[id] = line;
            } else if (line.size() >= 3 && line.at(2) == "OpFunction") {
                break;
            }
            line.clear();
            word.clear();
            continue;
        }

        word += c;
    }

    spvTextDestroy(resultText);
    spvContextDestroy(context);
}

void ShaderResource::dumpBindings() {
    PRINT("Dump SPIR-V descriptors:")
    for (auto& binding : bindings) {
        PRINT("name: " << binding.first
              << ", binding: " << binding.second.binding
              << ", descriptorType: " << binding.second.descriptorType)
    }
}

void ShaderResource::dumpLocations() {
    PRINT("Dump SPIR-V inputs:")
    for (auto& input : locations) {
        PRINT("name: " << input.first
              << ", location: " << input.second.location
              << ", format: " << input.second.format)
    }
}
