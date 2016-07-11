#pragma once
#include "../../Core/Object.h"
#include <GL/glew.h>

const std::string folder = "Data/Shader";

class Shader : public Object {

public:
    Shader(GLenum type);
    bool load(const std::string& path);
    GLuint getId() const { return id; }
    GLenum getType() const { return type; }
private:
    std::string source;
    GLuint id;
    GLenum type;
};
