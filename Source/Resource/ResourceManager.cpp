#include "ResourceManager.h"

ResourceManager::ResourceManager() {

}

void ResourceManager::loadAll() {

}

void ResourceManager::releaseAll() {
    for (auto resource : resources) {
        resource.second->release();
    }
}

Font* ResourceManager::getFont(std::string name) {
    return static_cast<Font*>(resources[name]);
}
