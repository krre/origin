#include "Octree.h"
#include "JsonStorage.h"
#include <fstream>

namespace Origin {

Octree::Octree(Object* parent) : Object(parent) {
    storage = new JsonStorage(this);
}

Octree::~Octree() {
}

void Octree::load(const std::string& path) {
    std::ifstream file(path);
    if (!file.is_open()) {
        throw std::runtime_error("Failed open file: " + path);
    }

    std::string text = std::string((std::istreambuf_iterator<char>(file)), (std::istreambuf_iterator<char>()));
//    source = json::parse(text);
}

} // Origin
