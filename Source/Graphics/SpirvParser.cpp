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

    std::vector<std::vector<std::string>> OpName;
    std::vector<std::vector<std::string>> OpDecorate;
    std::map<std::string, std::vector<std::string>> instructions;
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
                OpName.push_back(line);
            } else if (firstWord == "OpDecorate") {
                OpDecorate.push_back(line);
            } else if (firstWord.at(0) == '%') {
                // Remove elements from 0 to 1 index (%i and =)
                line.erase(line.begin(), line.begin() + 1);
                instructions[firstWord] = line;
            }
            line.clear();
            word.clear();
            continue;
        }

        word += c;
    }

    spvTextDestroy(resultText);

    // Fill code structures
    std::string id;
    std::string name;
    for (int i = 0; i < OpName.size(); i++) {
        std::vector<std::string>& nameLine = OpName.at(i);
        id = nameLine.at(1);
        name = nameLine.at(2);

        for (int j = 0; j < OpDecorate.size(); j++) {
            std::vector<std::string>& decorateLine = OpDecorate.at(j);
            if (decorateLine.at(1) == id) {
                Attributes attributes = {};
                bool isDescriptor = false;
                if (decorateLine.at(2) == "Binding") {
                    attributes.binding = std::stoi(decorateLine.at(3));
                    isDescriptor = true;
                }

                if (decorateLine.at(2) == "Location") {
                    attributes.location = std::stoi(decorateLine.at(3));
                    isDescriptor = true;
                }

                if (decorateLine.at(2) == "DescriptorSet") {
                    attributes.descriptorSet = std::stoi(decorateLine.at(3));
                    isDescriptor = true;
                }

                if (isDescriptor) {
                    bool isUpdate = false;
                    for (int k = 0; k < descriptors.size(); k++) {
                        if (descriptors.at(k).name == name) {
                            descriptors.at(k).binding = attributes.binding;
                            descriptors.at(k).location = attributes.location;
                            descriptors.at(k).descriptorSet = attributes.descriptorSet;
                            isUpdate = true;
                            break;
                        }
                    }

                    if (!isUpdate) {
                        attributes.name = name;
                        descriptors.push_back(attributes);
                    }
                }
            }
        }
    }
}
