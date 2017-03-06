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
    spv_diagnostic diagnostic = nullptr;
    spv_text resultText = nullptr;
    spvBinaryToText(context, code, count, 0, &resultText, &diagnostic);
    if (diagnostic) {
      spvDiagnosticPrint(diagnostic);
      spvDiagnosticDestroy(diagnostic);
      assert(false);
    }

//    PRINT("================")
//    PRINT(resultText->str)

    std::vector<std::vector<std::string>> document;
    std::vector<std::string> line;
    std::string word;

    int i = 0;
    while (i < resultText->length) {
        char c = resultText->str[i++];
        if (c == ' ') {
            line.push_back(word);
            word.clear();
            continue;
        }

        if (c == '\n') {
            document.push_back(line);
            line.clear();
            continue;
        }
        word += c;
    }

    spvTextDestroy(resultText);
}
