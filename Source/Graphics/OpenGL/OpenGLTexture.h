#pragma once
#include "Graphics/Texture.h"

namespace Origin {

class OpenGLTexture : public Texture {

public:
    OpenGLTexture(const std::string& path);
};

} // Origin
