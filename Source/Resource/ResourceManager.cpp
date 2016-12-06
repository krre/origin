#include "ResourceManager.h"
#include "ShaderResource.h"
#include "../Core/App.h"

ResourceManager::ResourceManager() {
    dataPath = App::getCurrentPath() + "/Data";
    shaderPath = dataPath + "/Shader";
    fontPath = dataPath + "/Font";
    octreePath = dataPath + "/Octree";
    loadAll();
}

void ResourceManager::loadAll() {
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

    auto baseVertShader = std::make_shared<ShaderResource>();
    baseVertShader->load(shaderPath + "/Base.vert.spv");
    resources["BaseVertShader"] = baseVertShader;

    auto baseFragShader = std::make_shared<ShaderResource>();
    baseFragShader->load(shaderPath + "/Base.frag.spv");
    resources["BaseFragShader"] = baseFragShader;

    auto voxelVertShader = std::make_shared<ShaderResource>();
    voxelVertShader->load(shaderPath + "/Voxel.vert.spv");
    resources["VoxelVertShader"] = voxelVertShader;

    auto voxelFragShader = std::make_shared<ShaderResource>();
    voxelFragShader->load(shaderPath + "/Voxel.frag.spv");
    resources["VoxelFragShader"] = voxelFragShader;
}
