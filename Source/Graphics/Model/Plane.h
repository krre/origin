#pragma once
#include "../../SceneGraph/Node.h"
#include "../OpenGL/Shader.h"
#include "../OpenGL/Program.h"

class Plane : public Node {

public:
    Plane(int width, int height);
    void draw() override;
private:
    int width;
    int height;
    Shader vertexShader;
    Shader fragmentShader;
    Program programShader;
    GLuint vao;
};
