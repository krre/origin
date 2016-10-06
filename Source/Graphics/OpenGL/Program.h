#pragma once
#include "../../Core/Object.h"
#include "Shader.h"
#include <GL/glew.h>
#include <vector>

class Program : public Object {

public:
    Program();
    void addShader(const Shader& shader);
    bool link();
    void bind();
    void release();
    GLuint getId() const { return id; }

private:
    GLuint id;
    std::vector<GLuint> shaders;
};
