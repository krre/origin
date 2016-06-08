#include "Buffer.h"

Buffer::Buffer(GLenum type) : type(type) {
    glGenBuffers(1, &id);
    bind();
}

void Buffer::setData(const void* data, int count) {
    glBufferData(type, count, data, GL_STATIC_DRAW);
}

void Buffer::bind() {
    glBindBuffer(type, id);
}
