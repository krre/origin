#pragma once
#include "Graphics/ShaderProgram.h"

namespace Origin {

class OpenGLShaderProgram : public ShaderProgram {

public:
    OpenGLShaderProgram(const std::string& name);
    ~OpenGLShaderProgram();

};

} // Origin
