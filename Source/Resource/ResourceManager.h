#pragma once
#include "Core/Singleton.h"
#include "Resource/Resource.h"
#include <map>

#undef HAVE_STDINT_H
#include <ft2build.h>
#include FT_FREETYPE_H

namespace Origin {

class ResourceManager : public Singleton<ResourceManager> {

public:
    ResourceManager();
    ~ResourceManager();

    template <typename T> T* load(const std::string& path) {
        auto it = resources.find(path);
        if (it == resources.end()) {
            resources[path] = std::make_shared<T>();
            resources[path]->load(resourcesPath + "/" + path);
        }

        return static_cast<T*>(resources[path].get());
    }

    void free(const std::string& path);

    static const std::string& getDataPath() { return resourcesPath; }

private:
    std::map<std::string, std::shared_ptr<Resource>> resources;
    static std::string resourcesPath;
    FT_Library ft;
};

} // Origin
