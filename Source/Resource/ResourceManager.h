#pragma once
#include "Core/SingleObject.h"
#include "Resource/Resource.h"
#include <map>

#undef HAVE_STDINT_H
#include <ft2build.h>
#include FT_FREETYPE_H

namespace Origin {

class ResourceManager : public SingleObject<ResourceManager> {

public:
    ResourceManager(Object* parent = nullptr);
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
    void cleanup();

    static const std::string& getDataPath() { return resourcesPath; }

    const FT_Library& getFreeTypeHandle() const { return ft; }

private:
    std::map<std::string, std::shared_ptr<Resource>> resources;
    static std::string resourcesPath;
    FT_Library ft;
};

} // Origin
