#include "SpirvParser.h"
#include <assert.h>

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
    PRINT("================")
    PRINT(resultText->str)
    if (diagnostic) {
      spvDiagnosticPrint(diagnostic);
      spvDiagnosticDestroy(diagnostic);
      assert(false);
    }
    spvTextDestroy(resultText);
}
