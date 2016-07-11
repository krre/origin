#include "ResourceManager.h"
#include "../Core/App.h"

ResourceManager::ResourceManager() {
    dataPath = App::getAbsolutePath() + "/Data";
    shaderPath = dataPath + "/Shader";
    fontPath = dataPath + "/Font";
}

void ResourceManager::loadAll() {
    // Effects
    Effect* baseEffect = new Effect();
    baseEffect->setVertShaderPath(shaderPath + "/Base.vert");
    baseEffect->setFragShaderPath(shaderPath + "/Base.frag");
    baseEffect->load();
    resources["BaseEffect"] = baseEffect;

    Effect* fontEffect = new Effect();
    fontEffect->setVertShaderPath(shaderPath + "/Font.vert");
    fontEffect->setFragShaderPath(shaderPath + "/Font.frag");
    fontEffect->load();
    resources["FontEffect"] = fontEffect;

    // Fonts
    Font* iconsolataFont = new Font();
    iconsolataFont->load(fontPath + "/inconsolatalgc.ttf");
    resources["IconsolataFont"] = iconsolataFont;
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
