#include "World.h"
#include "Base/Game.h"
#include "Core/Utils.h"
#include <experimental/filesystem>

static Origin::World* instance = nullptr;

namespace fs = std::experimental::filesystem;

namespace Origin {

World::World(Object* parent) : Object(parent) {
    instance = this;
}

void World::create(const std::string& name) {
    instance->savePath = getSavesDirectory() + Utils::getPathSeparator() + name;
    fs::create_directory(instance->savePath);
    PRINT("Create world: " << instance->savePath)
}

void World::remove(const std::string& name) {
    std::string removePath = getSavesDirectory() + Utils::getPathSeparator() + name;
    fs::remove_all(removePath);
    PRINT("Remove world: " << removePath)
}

void World::load(const std::string& name) {
    instance->savePath = getSavesDirectory() + Utils::getPathSeparator() + name;
    PRINT("Load world: " << instance->savePath)
}

void World::save() {
    PRINT("Save world: " << instance->savePath)
}

std::string World::getSavesDirectory() {
    std::string directoryPath = Game::getCurrentDirectory() + Utils::getPathSeparator() + "Saves";
    if (!fs::exists(directoryPath)) {
        fs::create_directory(directoryPath);
    }

    return directoryPath;
}

} // Origin
