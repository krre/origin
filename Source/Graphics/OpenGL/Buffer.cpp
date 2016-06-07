#include "Buffer.h"

Buffer::Buffer(GLenum type) : type(type) {
    glGenBuffers(1, &id);
    glBindBuffer(type, id);
}

void Buffer::setData(const void* data, int count) {
    glBufferData(type, count, data, GL_STATIC_DRAW);
}
