#include "VertexBuffer.h"

VertexBuffer::VertexBuffer(GLenum type) : type(type) {
    glGenBuffers(1, &id);
    glBindBuffer(type, id);
}

void VertexBuffer::setData(const void* data, int count) {
    glBufferData(type, count, data, GL_STATIC_DRAW);
}
