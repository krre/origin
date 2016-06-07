#include "VertexArrayObject.h"

VertexArrayObject::VertexArrayObject() {
    glGenVertexArrays(1, &id);
    glBindVertexArray(id);
}
