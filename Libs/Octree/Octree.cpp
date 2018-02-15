#include "Octree.h"
#include "JsonStorage.h"

namespace Origin {

Octree::Octree(Object* parent) : Object(parent) {
    storage = new JsonStorage(this);
}

Octree::~Octree() {

}

} // Origin
