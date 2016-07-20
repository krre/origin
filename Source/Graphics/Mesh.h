#pragma once
#include "../Core/Object.h"
#include "OpenGL/VertexArray.h"
#include "OpenGL/Buffer.h"
#include "ShaderGroup.h"
#include <vector>
#include <glm/ext.hpp>

class Mesh : public Object {

public:
    Mesh();
    VertexArray* getVAO() { return &VAO; }
    Buffer* getVBO() { return &VBO; }

    const std::vector<GLfloat>& getVerticles() const { return verticles; }
    const std::vector<int>& getIndices() const { return indices; }

    void setup();
    void setShaderGroup(ShaderGroup* shaderGroup);
    ShaderGroup* getShaderGroup() { return shaderGroup; }
    void draw();

protected:
    std::vector<GLfloat> verticles;
    std::vector<int> indices;

private:
    VertexArray VAO;
    Buffer VBO;
    ShaderGroup* shaderGroup;
};
