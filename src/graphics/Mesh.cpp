#include "Mesh.h"

Mesh::Mesh() {
}

void Mesh::setVertices(const std::vector<float> vertices) {
    this->m_vertices = vertices;
}

void Mesh::setIndices(const std::vector<uint32_t> indices) {
    this->m_indices = indices;
}
