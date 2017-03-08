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
    std::map<std::string, VkDescriptorType> types;
    std::map<std::string, Attributes> attributes;
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
                    types[id] = VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER;
                } else if (decorateName == "BufferBlock") {
                    types[id] = VK_DESCRIPTOR_TYPE_STORAGE_BUFFER;
                } else if (decorateName == "Binding") {
                    if (attributes.find(id) == attributes.end()) {
                        attributes[id] = {};
                    }
                    attributes.at(id).binding = std::stoi(line.at(3));
                } else if (decorateName == "Location") {
                    if (attributes.find(id) == attributes.end()) {
                        attributes[id] = {};
                    }
                    attributes.at(id).location = std::stoi(line.at(3));
                } else if (decorateName == "DescriptorSet") {
                    if (attributes.find(id) == attributes.end()) {
                        attributes[id] = {};
                    }
                    attributes.at(id).descriptorSet = std::stoi(line.at(3));
                }


            } else if (firstWord.at(0) == '%') {

            }
            line.clear();
            word.clear();
            continue;
        }

        word += c;
    }

    spvTextDestroy(resultText);
}

void SpirvParser::dumpDescriptors() {
    for (auto& descriptor : descriptors) {
//        PRINT("name: " << descriptor.name << ", location: " << descriptor.location  << ", descriptorSet: " << descriptor.descriptorSet << ", binding: " << descriptor.binding)
    }
}
