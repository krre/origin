#pragma once
#include "../../Core/Object.h"
#include <GL/glew.h>

class Buffer : public Object {

public:
    Buffer(GLenum type);
    GLuint getId() const { return id; }
    GLenum getType() const { return type; }

private:
    GLenum type;
    GLuint id;
};
