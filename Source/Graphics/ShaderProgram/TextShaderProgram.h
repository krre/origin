#pragma once
#include "ShaderProgram.h"

class TextShaderProgram : public ShaderProgram {

public:
    friend class DebugHUD;

    TextShaderProgram(const Vulkan::Device* device);
};
