#include "SpirvParser.h"
#include <assert.h>
#include <vector>
#include <map>

SpirvParser::SpirvParser() {
    context = spvContextCreate(SPV_ENV_UNIVERSAL_1_0);
}

SpirvParser::~SpirvParser() {
    spvContextDestroy(context);
}

void SpirvParser::parse(const uint32_t* code, size_t count) {
    descriptors.clear();
    spv_diagnostic diagnostic = nullptr;
    spv_text resultText = nullptr;
    spvBinaryToText(context, code, count, 0, &resultText, &diagnostic);
    if (diagnostic) {
      spvDiagnosticPrint(diagnostic);
      spvDiagnosticDestroy(diagnostic);
      assert(false);
    }

//    PRINT(resultText->str)
//    PRINT("================")

    std::map<std::string, std::string> names;
    std::map<std::string, VkDescriptorType> descriptorTypes;
    std::map<std::string, Attributes> attributes;
    std::map<std::string, std::string> typePointers;
    std::vector<std::string> line;
    std::string word;

    // Parse SPIR-V text code to vector of lines
    int i = 0;
    while (i < resultText->length) {
        char c = resultText->str[i++];
        if (c == ' ') {
            line.push_back(word);
            word.clear();
            continue;
        }

        if (c == '\n') {
            line.push_back(word);
            std::string firstWord = line.at(0);
            if (firstWord == "OpName") {
                names[line.at(1)] = line.at(2);
            } else if (firstWord == "OpDecorate") {
                std::string& id = line.at(1);
                std::string& decorateName = line.at(2);

                if (decorateName == "Block") {
                    descriptorTypes[id] = VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER;
                } else if (decorateName == "BufferBlock") {
                    descriptorTypes[id] = VK_DESCRIPTOR_TYPE_STORAGE_BUFFER;
                } else if (decorateName == "Binding") {
                    if (attributes.find(id) == attributes.end()) {
                        attributes[id] = {};
                    }
                    attributes.at(id).binding = std::stoi(line.at(3));
                    attributes.at(id).name = names.at(id);
                } else if (decorateName == "Location") {
                    if (attributes.find(id) == attributes.end()) {
                        attributes[id] = {};
                    }
                    attributes.at(id).location = std::stoi(line.at(3));
                    attributes.at(id).name = names.at(id);
                } else if (decorateName == "DescriptorSet") {
                    if (attributes.find(id) == attributes.end()) {
                        attributes[id] = {};
                    }
                    attributes.at(id).descriptorSet = std::stoi(line.at(3));
                    attributes.at(id).name = names.at(id);
                }


            } else if (firstWord.at(0) == '%') {
                std::string& id = firstWord;
                if (line.at(2) == "OpTypePointer") {
                    typePointers[id] = line.at(4);
                } else if (line.at(2) == "OpVariable") {
                    std::string& typePointerId = line.at(3);
                    if (typePointers.find(typePointerId) != typePointers.end()) {
                        std::string& descriptorTypeId = typePointers.at(typePointerId);
                        if (descriptorTypes.find(descriptorTypeId) != descriptorTypes.end()) {
                            VkDescriptorType descriptorType = descriptorTypes.at(descriptorTypeId);
                            attributes.at(id).type = descriptorType;
                        }
                    }
                }
            } else if (line.size() == 3 && line.at(2) == "OpFunction") {
                break;
            }
            line.clear();
            word.clear();
            continue;
        }

        word += c;
    }

    for (auto& it : attributes) {
        descriptors[it.second.name] = it.second;
    }

    spvTextDestroy(resultText);
}

void SpirvParser::dumpDescriptors() {
    for (auto& it : descriptors) {
        PRINT("name: " << it.second.name << ", location: " << it.second.location  << ", descriptorSet: " << it.second.descriptorSet << ", binding: " << it.second.binding << ", type: " << it.second.type)
    }
}
