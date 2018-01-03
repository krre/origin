#include "Octree.h"
#include "Core/Utils.h"
#include <fstream>
#include <bitset>

namespace Origin {

Octree::Octree() {

}

void Octree::load(const std::string& path) {
    std::ifstream file(path);
    if (!file.is_open()) {
        throw std::runtime_error("Failed open file: " + path);
        return;
    }

    std::string text = std::string((std::istreambuf_iterator<char>(file)), (std::istreambuf_iterator<char>()));
    source = json::parse(text);
}

void Octree::draw() {

}

std::shared_ptr<std::vector<uint32_t>> Octree::data() {
    return Utils::jsonToBinary(source);
}

} // Origin
