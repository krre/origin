#include "VertexArray.h"

VertexArray::VertexArray() {
    glGenVertexArrays(1, &id);
}

void VertexArray::bind() {
    glBindVertexArray(id);
}

void VertexArray::unbind() {
    glBindVertexArray(0);
}
