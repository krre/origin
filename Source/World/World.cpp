#include "World.h"

namespace Origin {

World::World(Object* parent) : Object(parent) {

}

void World::create(std::string& filePath) {
    this->filePath = filePath;
    PRINT("create world " << filePath)
}

void World::load(std::string& filePath) {
    PRINT("create world " << filePath)
            this->filePath = filePath;
}

void World::save() {
    PRINT("save world " << filePath)
}

} // Origin
