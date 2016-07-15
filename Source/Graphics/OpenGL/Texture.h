#pragma once
#include "../../Core/Object.h"
#include <GL/glew.h>

class Texture : public Object {

public:
    Texture(GLenum type);
    GLuint getId() const { return id; }
    GLenum getType() const { return type; }
    void bind();
    void unbind();

private:
    GLenum type;
    GLuint id;
};
