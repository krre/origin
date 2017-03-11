#pragma once
#include "ShaderProgram.h"
#include "../Vulkan/Sampler.h"
#include "../Vulkan/Image/ImageView.h"
#include "../Vulkan/Image/Image.h"
#include "../../UI/Text/Font.h"

class TextShaderProgram : public ShaderProgram {

public:
    friend class DebugHUD;

    TextShaderProgram(const Vulkan::Device* device);

private:
    Vulkan::Sampler sampler;
    Vulkan::ImageView samplerImageView;
    Vulkan::Image samplerImage;
    Font* font;
};
