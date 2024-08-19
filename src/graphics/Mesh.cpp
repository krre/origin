#include "Mesh.h"

Mesh::Mesh() {
}

void Mesh::setVertices(const std::vector<float> vertices) {
    m_vertices = vertices;
}

void Mesh::setIndices(const std::vector<uint32_t> indices) {
    m_indices = indices;
}
