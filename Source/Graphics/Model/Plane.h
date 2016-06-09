#pragma once
#include "../../Scene/Node.h"
#include "../OpenGL/Shader.h"
#include "../OpenGL/Program.h"
#include "../OpenGL/VertexArray.h"
#include "../OpenGL/Buffer.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

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
    VertexArray vao;
    Buffer vertexBuffer;
    Buffer colorBuffer;
    GLuint matrix;
    glm::mat4 mvp; // model-view-projection
};
