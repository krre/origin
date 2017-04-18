#include "Core/App.h"
#include "ResourceManager.h"
#include "ShaderResource.h"

ResourceManager::ResourceManager() {
    dataPath = App::getCurrentPath() + "/Data";
}

ResourceManager::~ResourceManager() {
    resources.clear();
}

void ResourceManager::free(const std::string& path) {
    resources.erase(path);
}
