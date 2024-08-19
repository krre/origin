#include "base/Game.h"
#include "ResourceManager.h"

std::string ResourceManager::s_resourcesPath = Game::currentDirectory() + "/data";

ResourceManager::ResourceManager(Object* parent) : SingleObject(parent) {
    if (FT_Init_FreeType(&m_ft)) {
        throw std::runtime_error("Could not init freetype library");
    }
}

ResourceManager::~ResourceManager() {
    m_resources.clear();
    FT_Done_FreeType(m_ft);
}

void ResourceManager::free(const std::string& path) {
    m_resources.erase(path);
}

void ResourceManager::cleanup() {
    m_resources.clear();
}
