#include "Base/Game.h"
#include "ResourceManager.h"

namespace Origin {

std::string ResourceManager::resourcesPath = Game::getCurrentDirectory() + "/Data";

ResourceManager::ResourceManager(Object* parent) : SingleObject(parent) {
    if (FT_Init_FreeType(&ft)) {
        throw std::runtime_error("Could not init freetype library");
    }
}

ResourceManager::~ResourceManager() {
    resources.clear();
    FT_Done_FreeType(ft);
}

void ResourceManager::free(const std::string& path) {
    resources.erase(path);
}

void ResourceManager::cleanup() {
    resources.clear();
}

} // Origin
