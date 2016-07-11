#pragma once
#include "../Core/Object.h"
#include "OpenGL/VertexArray.h"
#include "OpenGL/Buffer.h"

class Mesh : public Object {

public:
    Mesh();
    VertexArray* getVao() { return &vao; }
    Buffer* getVbo() { return &vbo; }

private:
    VertexArray vao;
    Buffer vbo;
};
