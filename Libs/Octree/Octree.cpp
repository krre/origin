#include "Octree.h"
#include "JsonStorage.h"
#include <fstream>

namespace Origin {

Octree::Octree(Object* parent) : Object(parent) {
    create();
}

Octree::~Octree() {
}

void Octree::create() {
    storage = {};
    build();
}

void Octree::load(const std::string& path) {
    std::ifstream file(path);
    if (!file.is_open()) {
        throw std::runtime_error("Failed open file: " + path);
    }

    std::string text = std::string((std::istreambuf_iterator<char>(file)), (std::istreambuf_iterator<char>()));
    storage = json::parse(text);
}

void Octree::build(Octree::SurfaceFlags flags) {
    vertices.clear();

    uint32_t numFlags = static_cast<uint32_t>(flags);

    Vertex vertex = {};
    vertex.color =  { 1.0f, 0.0f, 0.0f, 1.0f };

    vertex.pos = { -1.0, 1.0, 1.0, 1.0f };
    vertices.push_back(vertex);

    vertex.pos = { 1.0, 1.0, 1.0, 1.0f };
    vertices.push_back(vertex);

    vertex.pos = { -1.0, -1.0, 1.0, 1.0f };
    vertices.push_back(vertex);
}

const std::vector<Octree::Vertex>& Octree::getVertices() const {
    return vertices;
}

void Octree::setSubstance(const Substance& substance) {
    this->substance = substance;
}

} // Origin
