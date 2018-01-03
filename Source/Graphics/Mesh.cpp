#include "Mesh.h"

namespace Origin {

Mesh::Mesh() {
}

void Mesh::setVertices(const std::vector<float> vertices) {
    this->vertices = vertices;
}

void Mesh::setIndices(const std::vector<uint32_t> indices) {
    this->indices = indices;
}

} // Origin
