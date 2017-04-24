#include "Mesh.h"

Mesh::Mesh() {
}

void Mesh::setVertices(const std::vector<float> vertices) {
    this->vertices = vertices;
}

void Mesh::setIndices(const std::vector<uint16_t> indices) {
    this->indices = indices;
}
