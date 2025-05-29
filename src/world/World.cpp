#include "World.h"
#include "base/Game.h"
#include <core/Utils.h>
#include <core/Common.h>
#include <filesystem>

World::World(Object* parent) : SingleObject(parent) {
}

void World::create(const std::string& name) {
    get()->m_savePath = savesDirectory() + Core::Utils::pathSeparator() + name;
    std::filesystem::create_directory(get()->m_savePath);
    PRINT("Create world: " << get()->m_savePath)
}

void World::remove(const std::string& name) {
    std::string removePath = savesDirectory() + Core::Utils::pathSeparator() + name;
    std::filesystem::remove_all(removePath);
    PRINT("Remove world: " << removePath)
}

void World::load(const std::string& name) {
    get()->m_savePath = savesDirectory() + Core::Utils::pathSeparator() + name;
    PRINT("Load world: " << get()->m_savePath)
}

void World::save() {
    PRINT("Save world: " << get()->m_savePath)
}

std::string World::savesDirectory() {
    std::string directoryPath = Game::currentDirectory() + Core::Utils::pathSeparator() + "saves";
    if (!std::filesystem::exists(directoryPath)) {
        std::filesystem::create_directory(directoryPath);
    }

    return directoryPath;
}
