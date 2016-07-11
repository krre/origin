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
