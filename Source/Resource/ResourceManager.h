#pragma once
#include "../Core/Singleton.h"
#include "../Resource/Resource.h"
#include "../UI/Font.h"
#include "../Graphics/OpenGL/ShaderGroup.h"
#include "../Graphics/Voxel/Octree.h"
#include <map>

class ResourceManager : public Singleton<ResourceManager> {

public:
    ResourceManager();

    Font* getFont(const std::string& name);
    ShaderGroup* getShaderGroup(const std::string& name);
    Octree* getOctree(const std::string& name);

private:
    void loadAll();

    std::map<std::string, std::shared_ptr<Resource>> resources;
    std::string dataPath;
    std::string shaderPath;
    std::string fontPath;
    std::string octreePath;
};
