#pragma once
#include "../Core/Object.h"
#include <vector>

class Mesh : public Object {

public:
    Mesh();
    void setVertices(const std::vector<float> vertices);
    const std::vector<float>& getVertices() const { return vertices; }

    void setIndices(const std::vector<uint32_t> indices);
    const std::vector<uint32_t>& getIndices() const { return indices; }

    void draw();

private:
    std::vector<float> vertices;
    std::vector<uint32_t> indices;
};
