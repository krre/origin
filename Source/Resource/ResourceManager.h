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

    template <typename T> T* getResource(const std::string& name) {
        return static_cast<T*>(resources[name].get());
    }

private:
    void loadAll();

    std::map<std::string, std::shared_ptr<Resource>> resources;
    std::string dataPath;
    std::string shaderPath;
    std::string fontPath;
    std::string octreePath;
};
