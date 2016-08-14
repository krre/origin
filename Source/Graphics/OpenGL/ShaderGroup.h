#pragma once
#include "../Resource/Resource.h"
#include "Shader.h"
#include "Program.h"

class ShaderGroup : public Resource {

public:
    ShaderGroup();
    void setVertShaderPath(const std::string& path);
    void setFragShaderPath(const std::string& path);
    void load() override;
    void use();
    GLuint getProgram() { return program.getId(); }

private:
    Shader vertShader;
    Shader fragShader;
    Program program;

    std::string vertShaderPath;
    std::string fragShaderPath;
};
