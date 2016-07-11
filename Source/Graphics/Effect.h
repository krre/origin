#pragma once
#include "../Resource/Resource.h"
#include "OpenGL/Shader.h"
#include "OpenGL/Program.h"

class Effect : public Resource {

public:
    Effect();
    void setVertShaderPath(const std::string& path);
    void setFragShaderPath(const std::string& path);
    void load() override;
    void use();

private:
    Shader vertShader;
    Shader fragShader;
    Program program;

    std::string vertShaderPath;
    std::string fragShaderPath;
};
