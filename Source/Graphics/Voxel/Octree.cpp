#include "Octree.h"
#include <fstream>

Octree::Octree() {

}

void Octree::load(const std::string& path) {
    std::ifstream file(path);
    if (!file.is_open()) {
        error("Failed open file: " << path);
        return;
    }

    std::string text = std::string((std::istreambuf_iterator<char>(file)), (std::istreambuf_iterator<char>()));
    source = json::parse(text);
}

void Octree::draw() {

}
