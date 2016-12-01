#pragma once
#include "../Core/Object.h"
#include <vector>

class Mesh : public Object {

public:
    Mesh();
//    GLuint getVAO() { return vao; }
//    GLuint getVBO() { return vbo; }

//    const std::vector<GLfloat>& getVerticles() const { return verticles; }
    const std::vector<int>& getIndices() const { return indices; }

    void setup();
    void draw();

protected:
//    std::vector<GLfloat> verticles;
    std::vector<int> indices;

private:
//    GLuint vao;
//    GLuint vbo;
};
