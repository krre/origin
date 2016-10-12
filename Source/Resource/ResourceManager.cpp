#include "ResourceManager.h"
#include "../Core/App.h"

ResourceManager::ResourceManager() {
    dataPath = App::getCurrentPath() + "/Data";
    shaderPath = dataPath + "/Shader";
    fontPath = dataPath + "/Font";
    octreePath = dataPath + "/Octree";
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

    auto voxelShaderGroup = std::make_shared<ShaderGroup>();
    voxelShaderGroup->setVertShaderPath(shaderPath + "/Voxel.vert");
    voxelShaderGroup->setFragShaderPath(shaderPath + "/Voxel.frag");
    voxelShaderGroup->load();
    resources["VoxelShaderGroup"] = voxelShaderGroup;

    // Fonts
    auto iconsolataFont = std::make_shared<Font>();
    iconsolataFont->load(fontPath + "/inconsolatalgc.ttf");
    resources["IconsolataFont"] = iconsolataFont;

    // Octrees
    auto groundOctree = std::make_shared<Octree>();
    groundOctree->load(octreePath + "/Ground.json");
    resources["GroundOctree"] = groundOctree;

    auto treeOctree = std::make_shared<Octree>();
    treeOctree->load(octreePath + "/Tree.json");
    resources["TreeOctree"] = treeOctree;

    auto chamomileOctree = std::make_shared<Octree>();
    chamomileOctree->load(octreePath + "/Chamomile.json");
    resources["ChamomileOctree"] = chamomileOctree;
}

Font* ResourceManager::getFont(const std::string& name) {
    return static_cast<Font*>(resources[name].get());
}

ShaderGroup* ResourceManager::getShaderGroup(const std::string& name) {
    return static_cast<ShaderGroup*>(resources[name].get());
}

Octree *ResourceManager::getOctree(const std::string& name) {
    return static_cast<Octree*>(resources[name].get());
}
