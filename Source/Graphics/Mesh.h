#pragma once
#include "../Core/Object.h"
#include <vector>

class Mesh : public Object {

public:
    Mesh();
    void setVertices(const std::vector<float> vertices);
    const std::vector<float>& getVertices() const { return vertices; }
    uint32_t getVerticesSize() const { return sizeof(vertices[0]) * vertices.size(); }

    void setIndices(const std::vector<uint16_t> indices);
    const std::vector<uint16_t>& getIndices() const { return indices; }
    uint32_t getIndicesSize() const { return sizeof(indices[0]) * indices.size(); }

    void draw();

private:
    std::vector<float> vertices;
    std::vector<uint16_t> indices;
};
