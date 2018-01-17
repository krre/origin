#pragma once
#include "Graphics/ShaderProgram.h"

namespace Origin {

class OpenGLShaderProgram : public ShaderProgram {

public:
    OpenGLShaderProgram();
    ~OpenGLShaderProgram();

    void addShader(ShaderType type, const std::string& name) override;

private:

};

} // Origin
