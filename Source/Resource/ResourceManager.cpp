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

Font* ResourceManager::getFont(const std::string& name) {
    return static_cast<Font*>(resources[name]);
}

Effect* ResourceManager::getEffect(const std::string& name) {
    return static_cast<Effect*>(resources[name]);
}
