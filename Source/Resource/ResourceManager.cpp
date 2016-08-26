#include "ResourceManager.h"
#include "../Core/App.h"

ResourceManager::ResourceManager() {
    dataPath = App::getAbsolutePath() + "/Data";
    shaderPath = dataPath + "/Shader";
    fontPath = dataPath + "/Font";
    loadAll();
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

    auto lightShaderGroup = std::make_shared<ShaderGroup>();
    lightShaderGroup->setVertShaderPath(shaderPath + "/Light.vert");
    lightShaderGroup->setFragShaderPath(shaderPath + "/Light.frag");
    lightShaderGroup->load();
    resources["LightShaderGroup"] = lightShaderGroup;

    auto surfaceShaderGroup = std::make_shared<ShaderGroup>();
    surfaceShaderGroup->setVertShaderPath(shaderPath + "/Surface.vert");
    surfaceShaderGroup->setFragShaderPath(shaderPath + "/Surface.frag");
    surfaceShaderGroup->load();
    resources["SurfaceShaderGroup"] = surfaceShaderGroup;

    auto voxelShaderGroup = std::make_shared<ShaderGroup>();
    voxelShaderGroup->setVertShaderPath(shaderPath + "/Voxel.vert");
    voxelShaderGroup->setFragShaderPath(shaderPath + "/Voxel.frag");
    voxelShaderGroup->load();
    resources["VoxelShaderGroup"] = voxelShaderGroup;

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
