#pragma once
#include "../../Core/Object.h"
#include <GL/glew.h>

class VertexArray : public Object {

public:
    VertexArray();
    GLuint getId() const { return id; }
    GLuint id;
};
