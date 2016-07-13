#include "ResourceManager.h"
#include "../Core/App.h"

ResourceManager::ResourceManager() {
    dataPath = App::getAbsolutePath() + "/Data";
    shaderPath = dataPath + "/Shader";
    fontPath = dataPath + "/Font";
}

ResourceManager::~ResourceManager() {
    releaseAll();
}

void ResourceManager::loadAll() {
    // ShaderGroups
    ShaderGroup* baseShaderGroup = new ShaderGroup();
    baseShaderGroup->setVertShaderPath(shaderPath + "/Base.vert");
    baseShaderGroup->setFragShaderPath(shaderPath + "/Base.frag");
    baseShaderGroup->load();
    resources["BaseShaderGroup"] = baseShaderGroup;

    ShaderGroup* fontShaderGroup = new ShaderGroup();
    fontShaderGroup->setVertShaderPath(shaderPath + "/Font.vert");
    fontShaderGroup->setFragShaderPath(shaderPath + "/Font.frag");
    fontShaderGroup->load();
    resources["FontShaderGroup"] = fontShaderGroup;

    // Fonts
    Font* iconsolataFont = new Font();
    iconsolataFont->load(fontPath + "/inconsolatalgc.ttf");
    resources["IconsolataFont"] = iconsolataFont;
}

void ResourceManager::releaseAll() {
    for (auto resource : resources) {
        resource.second->release();
        delete resource.second;
    }
    resources.clear();
}

Font* ResourceManager::getFont(const std::string& name) {
    return static_cast<Font*>(resources[name]);
}

ShaderGroup* ResourceManager::getShaderGroup(const std::string& name) {
    return static_cast<ShaderGroup*>(resources[name]);
}
