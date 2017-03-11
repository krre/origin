#include "../Core/App.h"
#include "ResourceManager.h"
#include "ShaderResource.h"

ResourceManager::ResourceManager() {
    dataPath = App::getCurrentPath() + "/Data";

    if (FT_Init_FreeType(&ft)) {
        ERROR("Could not init freetype library");
    }
}

ResourceManager::~ResourceManager() {
    FT_Done_FreeType(ft);
}

void ResourceManager::free(const std::string& path) {
    resources.erase(path);
}

