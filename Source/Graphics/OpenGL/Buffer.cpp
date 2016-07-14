#include "Buffer.h"

Buffer::Buffer(GLenum type) : type(type) {
    glGenBuffers(1, &id);
}

void Buffer::setData(const void* data, int count) {
    glBufferData(type, count, data, GL_STATIC_DRAW);
}

void Buffer::bind() {
    glBindBuffer(type, id);
}

void Buffer::unbind() {
    glBindBuffer(type, 0);
}
