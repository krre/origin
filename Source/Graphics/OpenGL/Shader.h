#pragma once
#include "../../Core/Object.h"
#include <GL/glew.h>

const string folder = "Data/Shader";

class Shader : public Object {

public:
    Shader();
    bool load(const string& path, GLenum type);
    GLuint getId() const { return id; }
private:
    string source;
    GLuint id;
};
