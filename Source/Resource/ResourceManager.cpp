#include "Core/Application.h"
#include "ResourceManager.h"

namespace Origin {

ResourceManager::ResourceManager() {
    dataPath = Application::getCurrentPath() + "/Data";
}

ResourceManager::~ResourceManager() {
    resources.clear();
}

void ResourceManager::free(const std::string& path) {
    resources.erase(path);
}

} // Origin
