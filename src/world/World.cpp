#include "World.h"
#include "base/Game.h"
#include "core/Utils.h"
#include <experimental/filesystem>

namespace fs = std::experimental::filesystem;

World::World(Object* parent) : SingleObject(parent) {
}

void World::create(const std::string& name) {
    get()->savePath = getSavesDirectory() + Core::Utils::getPathSeparator() + name;
    fs::create_directory(get()->savePath);
    PRINT("Create world: " << get()->savePath)
}

void World::remove(const std::string& name) {
    std::string removePath = getSavesDirectory() + Core::Utils::getPathSeparator() + name;
    fs::remove_all(removePath);
    PRINT("Remove world: " << removePath)
}

void World::load(const std::string& name) {
    get()->savePath = getSavesDirectory() + Core::Utils::getPathSeparator() + name;
    PRINT("Load world: " << get()->savePath)
}

void World::save() {
    PRINT("Save world: " << get()->savePath)
}

std::string World::getSavesDirectory() {
    std::string directoryPath = Game::getCurrentDirectory() + Core::Utils::getPathSeparator() + "saves";
    if (!fs::exists(directoryPath)) {
        fs::create_directory(directoryPath);
    }

    return directoryPath;
}
