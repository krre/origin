#pragma once
#include "../Core/Object.h"
#include "OpenGL/VertexArray.h"
#include "OpenGL/Buffer.h"
#include "ShaderGroup.h"
#include <vector>

class Mesh : public Object {

public:
    Mesh();
    VertexArray* getVAO() { return &VAO; }
    Buffer* getVBO() { return &VBO; }

    const std::vector<GLfloat>& getVerticles() const { return verticles; }
    const std::vector<int>& getIndices() const { return indices; }

    void setup();
    void setShaderGroup(ShaderGroup* shaderGroup);
    void draw(float dt);

protected:
    std::vector<GLfloat> verticles;
    std::vector<int> indices;

private:
    VertexArray VAO;
    Buffer VBO;
    ShaderGroup* shaderGroup;
};
