#pragma once
#include "ShaderProgram.h"
#include "../Vulkan/Sampler.h"
#include "../../UI/Text/Font.h"

class TextShaderProgram : public ShaderProgram {

public:
    friend class DebugHUD;

    TextShaderProgram(const Vulkan::Device* device);
    Font* getFont() const { return font; }

private:
    Vulkan::Sampler sampler;
    Font* font;
};
