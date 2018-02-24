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
    uint32_t numFlags = static_cast<uint32_t>(flags);
    PRINT(numFlags)
    vertices.clear();
}

const std::vector<Octree::Vertex>& Octree::getVertices() const {
    return vertices;
}

void Octree::setSubstance(const Substance& substance) {
    this->substance = substance;
}

} // Origin
