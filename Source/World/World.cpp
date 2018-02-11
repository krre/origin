#include "World.h"
#include "Core/Game.h"
#include "Core/Utils.h"
#include <experimental/filesystem>

namespace fs = std::experimental::filesystem;

namespace Origin {

World::World(Object* parent) : Object(parent) {

}

void World::create(const std::string& name) {
    savePath = getSavesDirectory() + Utils::getPathSeparator() + name;
    fs::create_directory(savePath);
    PRINT("create world " << savePath)
}

void World::load(const std::string& name) {
    PRINT("create world " << name)
    this->savePath = name;
}

void World::save() {
    PRINT("save world " << savePath)
}

std::string World::getSavesDirectory() {
    std::string directoryPath = Game::getCurrentDirectory() + Utils::getPathSeparator() + "Saves";
    if (!fs::exists(directoryPath)) {
        fs::create_directory(directoryPath);
    }

    return directoryPath;
}

} // Origin
