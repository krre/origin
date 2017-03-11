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

    template <typename T> T* load(const std::string& path) {
        auto it = resources.find(path);
        if (it == resources.end()) {
            resources[path] = std::make_shared<T>();
            resources[path]->load(dataPath + "/" + path);
        }

        return static_cast<T*>(resources[path].get());
    }

    void free(const std::string& path);

    FT_Library getFreeTypeHandler() { return ft; }

private:
    std::map<std::string, std::shared_ptr<Resource>> resources;
    std::string dataPath;
    FT_Library ft;
};
