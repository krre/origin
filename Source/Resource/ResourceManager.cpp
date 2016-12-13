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
    resources["IconsolataFont"] = std::make_shared<Font>();
    resources["IconsolataFont"]->load(fontPath + "/inconsolatalgc.ttf");

    // Octrees
    resources["GroundOctree"] = std::make_shared<Octree>();
    resources["GroundOctree"]->load(octreePath + "/Ground.json");

    resources["TreeOctree"] = std::make_shared<Octree>();
    resources["TreeOctree"]->load(octreePath + "/Tree.json");

    resources["ChamomileOctree"] = std::make_shared<Octree>();
    resources["ChamomileOctree"]->load(octreePath + "/Chamomile.json");

    // Shaders
    resources["BaseVertShader"] = std::make_shared<ShaderResource>();
    resources["BaseVertShader"]->load(shaderPath + "/Base.vert.spv");

    resources["BaseFragShader"] = std::make_shared<ShaderResource>();
    resources["BaseFragShader"]->load(shaderPath + "/Base.frag.spv");

    resources["VoxelVertShader"] = std::make_shared<ShaderResource>();
    resources["VoxelVertShader"]->load(shaderPath + "/Voxel.vert.spv");

    resources["VoxelFragShader"] = std::make_shared<ShaderResource>();
    resources["VoxelFragShader"]->load(shaderPath + "/Voxel.frag.spv");
}
