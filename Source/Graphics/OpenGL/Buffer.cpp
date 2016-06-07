#include "Buffer.h"

Buffer::Buffer(GLenum type) : type(type) {
    glGenBuffers(1, &id);
    glBindBuffer(type, id);
}
