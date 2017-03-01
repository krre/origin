#pragma once
#include "../Core/Singleton.h"
#include "../Resource/Resource.h"
#include "../UI/Text/Font.h"
#include "../Graphics/Voxel/Octree.h"
#include <ft2build.h>
#undef HAVE_STDINT_H
#include FT_FREETYPE_H
#include <map>

class ResourceManager : public Singleton<ResourceManager> {

public:
    ResourceManager();
    ~ResourceManager();

    template <typename T> T* getResource(const std::string& name) {
        return static_cast<T*>(resources[name].get());
    }

    template <typename T> T* load(const std::string& path) {
        auto fullPath = dataPath + "/" + path;

    }

    FT_Library getFreeTypeHandler() { return ft; }

private:
    void loadAll();

    std::map<std::string, std::shared_ptr<Resource>> resources;
    std::string dataPath;
    std::string shaderPath;
    std::string fontPath;
    std::string octreePath;

    FT_Library ft;
};
