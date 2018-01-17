#include "Core/Application.h"
#include "ResourceManager.h"

namespace Origin {

std::string ResourceManager::resourcesPath = Application::getCurrentPath() + "/Data";

ResourceManager::ResourceManager() {
}

ResourceManager::~ResourceManager() {
    resources.clear();
}

void ResourceManager::free(const std::string& path) {
    resources.erase(path);
}

} // Origin
