#pragma once
#include "../../Core/Object.h"
#include <GL/glew.h>

class VertexArrayObject : public Object {

public:
    VertexArrayObject();
    GLuint getId() const { return id; }
    GLuint id;
};
