#pragma once
#include "../../Core/Object.h"
#include <GL/glew.h>

class Buffer : public Object {

public:
    Buffer(GLenum type);

private:
    GLenum type;
};
