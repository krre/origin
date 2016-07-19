#include "ResourceManager.h"
#include "../Core/App.h"

ResourceManager::ResourceManager() {
    dataPath = App::getAbsolutePath() + "/Data";
    shaderPath = dataPath + "/Shader";
    fontPath = dataPath + "/Font";
}

void ResourceManager::loadAll() {
    // ShaderGroups
    auto baseShaderGroup = std::make_shared<ShaderGroup>();
    baseShaderGroup->setVertShaderPath(shaderPath + "/Base.vert");
    baseShaderGroup->setFragShaderPath(shaderPath + "/Base.frag");
    baseShaderGroup->load();
    resources["BaseShaderGroup"] = baseShaderGroup;

    auto fontShaderGroup = std::make_shared<ShaderGroup>();
    fontShaderGroup->setVertShaderPath(shaderPath + "/Font.vert");
    fontShaderGroup->setFragShaderPath(shaderPath + "/Font.frag");
    fontShaderGroup->load();
    resources["FontShaderGroup"] = fontShaderGroup;

    // Fonts
    auto iconsolataFont = std::make_shared<Font>();
    iconsolataFont->load(fontPath + "/inconsolatalgc.ttf");
    resources["IconsolataFont"] = iconsolataFont;
}

Font* ResourceManager::getFont(const std::string& name) {
    return static_cast<Font*>(resources[name].get());
}

ShaderGroup* ResourceManager::getShaderGroup(const std::string& name) {
    return static_cast<ShaderGroup*>(resources[name].get());
}
