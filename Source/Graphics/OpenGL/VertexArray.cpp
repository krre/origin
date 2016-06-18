#include "VertexArray.h"

VertexArray::VertexArray() {
    glGenVertexArrays(1, &id);
    bind();
}

void VertexArray::bind() {
    glBindVertexArray(id);
}
