#include "World.h"
#include "base/Game.h"
#include <core/Utils.h>
#include <filesystem>

World::World(Object* parent) : SingleObject(parent) {
}

void World::create(const std::string& name) {
    get()->savePath = savesDirectory() + Core::Utils::getPathSeparator() + name;
    std::filesystem::create_directory(get()->savePath);
    PRINT("Create world: " << get()->savePath)
}

void World::remove(const std::string& name) {
    std::string removePath = savesDirectory() + Core::Utils::getPathSeparator() + name;
    std::filesystem::remove_all(removePath);
    PRINT("Remove world: " << removePath)
}

void World::load(const std::string& name) {
    get()->savePath = savesDirectory() + Core::Utils::getPathSeparator() + name;
    PRINT("Load world: " << get()->savePath)
}

void World::save() {
    PRINT("Save world: " << get()->savePath)
}

std::string World::savesDirectory() {
    std::string directoryPath = Game::currentDirectory() + Core::Utils::getPathSeparator() + "saves";
    if (!std::filesystem::exists(directoryPath)) {
        std::filesystem::create_directory(directoryPath);
    }

    return directoryPath;
}
