#include "SpirvParser.h"
#include <assert.h>
#include <vector>

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
            if (line.at(0) == "OpName") {
                OpName.push_back(line);
            } else if (line.at(0) == "OpDecorate") {
                OpDecorate.push_back(line);
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
                attributes.name = name;
                if (decorateLine.at(2) == "Binding") {
                    attributes.binding = std::stoi(decorateLine.at(3));
                    PRINT(name << " binding: " << attributes.binding)
                }

                if (decorateLine.at(2) == "Location") {
                    attributes.location = std::stoi(decorateLine.at(3));
                    PRINT(name << " location: " << attributes.location)
                }

                if (decorateLine.at(2) == "DescriptorSet") {
                    attributes.descriptorSet = std::stoi(decorateLine.at(3));
                    PRINT(name << " descriptorSet: " << attributes.descriptorSet)
                }
            }
        }
    }
}
