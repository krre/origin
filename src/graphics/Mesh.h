#pragma once
#include <core/Object.h>
#include <vector>

class Mesh : public Core::Object {
public:
    Mesh();

    void setVertices(const std::vector<float> vertices);
    const std::vector<float>& vertices() const { return m_vertices; }

    uint32_t verticesSize() const { return sizeof(m_vertices[0]) * m_vertices.size(); }

    void setIndices(const std::vector<uint32_t> indices);
    const std::vector<uint32_t>& indices() const { return m_indices; }

    uint32_t indicesSize() const { return sizeof(m_indices[0]) * m_indices.size(); }

private:
    std::vector<float> m_vertices;
    std::vector<uint32_t> m_indices;
};
