#include "JsonStorage.h"

namespace Octree {

JsonStorage::JsonStorage() {

}

JsonStorage::~JsonStorage() {

}

void JsonStorage::create() {
    for (int i = 0; i < 8; i++) {
        json node;
        node["substance"] = 0;
        root[i] = node;
    }
}

} // Octree
