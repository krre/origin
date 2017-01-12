#include "Mesh.h"
#include <assert.h>
#include <glm/ext.hpp>
#include <glm/glm.hpp>

Mesh::Mesh() {
}

void Mesh::setVertices(const std::vector<float> vertices) {
    this->vertices = vertices;
}

void Mesh::setIndices(const std::vector<uint16_t> indices) {
    this->indices = indices;
}

void Mesh::draw() {
}
