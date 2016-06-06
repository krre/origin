#pragma once
#include "../../Core/Object.h"
#include <GL/glew.h>

const string folder = "Data/Shader";

class Shader : public Object {

public:
    Shader(GLenum type);
    bool load(const string& path);
    GLuint getId() const { return id; }
    GLenum getType() const { return type; }
private:
    string source;
    GLuint id;
    GLenum type;
};
