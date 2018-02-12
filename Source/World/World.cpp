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
    PRINT("Create world: " << savePath)
}

void World::remove(const std::string& name) {
    std::string removePath = getSavesDirectory() + Utils::getPathSeparator() + name;
    fs::remove_all(removePath);
    PRINT("Remove world: " << removePath)
}

void World::load(const std::string& name) {
    this->savePath = getSavesDirectory() + Utils::getPathSeparator() + name;
    PRINT("Load world: " << savePath)
}

void World::save() {
    PRINT("Save world: " << savePath)
}

std::string World::getSavesDirectory() {
    std::string directoryPath = Game::getCurrentDirectory() + Utils::getPathSeparator() + "Saves";
    if (!fs::exists(directoryPath)) {
        fs::create_directory(directoryPath);
    }

    return directoryPath;
}

} // Origin
