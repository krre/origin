#include "JsonStorage.h"

namespace Origin {

JsonStorage::JsonStorage(Object* parent) : Object(parent) {

}

JsonStorage::~JsonStorage() {
}

void JsonStorage::create() {
    for (int i = 0; i < 8; i++) {
        json node;
        node["material"] = 0;
        root[i] = node;
    }
}

} // Origin
