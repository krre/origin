#pragma once
#include "../../Core/Object.h"
#include <GL/glew.h>

class VertexBuffer : public Object {

public:
    VertexBuffer(GLenum type);
    GLuint getId() const { return id; }
    GLenum getType() const { return type; }
    void setData(const void* data, int count);

private:
    GLenum type;
    GLuint id;
};
