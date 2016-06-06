#pragma once
#include "../../Core/Object.h"
#include <GL/glew.h>

class Buffer : public Object {

public:
    Buffer(GLenum type);
    GLuint getId() const { return id; }

private:
    GLenum type;
    GLuint id;
};
