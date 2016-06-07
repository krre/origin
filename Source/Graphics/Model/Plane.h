#pragma once
#include "../../SceneGraph/Node.h"
#include "../OpenGL/Shader.h"
#include "../OpenGL/Program.h"
#include "../OpenGL/VertexArray.h"
#include "../OpenGL/VertexBuffer.h"
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
    VertexBuffer buffer;
    GLuint matrix;
    glm::mat4 MVP;
};
