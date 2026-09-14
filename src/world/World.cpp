#include "World.h"
#include "base/Game.h"
#include <core/Utils.h>
#include <core/Common.h>
#include <filesystem>
#include <print>

World::World(Object* parent) : SingleObject(parent) {
}

void World::create(const std::string& name) {
    get()->m_savePath = savesDirectory() + Core::Utils::pathSeparator() + name;
    std::filesystem::create_directory(get()->m_savePath);
    std::println("Create world: {}", get()->m_savePath);
}

void World::remove(const std::string& name) {
    std::string removePath = savesDirectory() + Core::Utils::pathSeparator() + name;
    std::filesystem::remove_all(removePath);
    std::println("Remove world: {}", removePath);
}

void World::load(const std::string& name) {
    get()->m_savePath = savesDirectory() + Core::Utils::pathSeparator() + name;
    std::println("Load world: {}", get()->m_savePath);
}

void World::save() {
    std::println("Save world: {}", get()->m_savePath);
}

std::string World::savesDirectory() {
    std::string directoryPath = Game::currentDirectory() + Core::Utils::pathSeparator() + "saves";
    if (!std::filesystem::exists(directoryPath)) {
        std::filesystem::create_directory(directoryPath);
    }

    return directoryPath;
}
