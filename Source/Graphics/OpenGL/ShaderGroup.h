#pragma once
#include "../../Resource/Resource.h"
#include "Shader.h"
#include "Program.h"

class ShaderGroup : public Resource {

public:
    ShaderGroup();
    void loadShader(GLenum type, const std::string& path);
    void link();
    void bind();
    GLuint getProgram() { return program.getId(); }

private:
    Program program;
};
