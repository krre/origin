#include "../Core/App.h"
#include "ResourceManager.h"
#include "ShaderResource.h"

ResourceManager::ResourceManager() {
    dataPath = App::getCurrentPath() + "/Data";
    shaderPath = dataPath + "/Shader";

    if (FT_Init_FreeType(&ft)) {
        ERROR("Could not init freetype library");
    }

    loadAll();
}

ResourceManager::~ResourceManager() {
    FT_Done_FreeType(ft);
}

void ResourceManager::loadAll() {

}
