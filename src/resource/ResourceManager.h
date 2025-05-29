#pragma once
#include "resource/Resource.h"
#include <core/SingleObject.h>
#include <map>
#include <memory>

#undef HAVE_STDINT_H
#include <ft2build.h>
#include FT_FREETYPE_H

class ResourceManager : public Core::SingleObject<ResourceManager> {
public:
    ResourceManager(Object* parent = nullptr);
    ~ResourceManager();

    template <typename T>
    T* load(const std::string& path) {
        auto it = m_resources.find(path);
        if (it == m_resources.end()) {
            m_resources[path] = std::make_shared<T>();
            m_resources[path]->load(s_resourcesPath + "/" + path);
        }

        return static_cast<T*>(m_resources[path].get());
    }

    void free(const std::string& path);
    void cleanup();

    static const std::string& dataPath() { return s_resourcesPath; }

    const FT_Library& freeTypeHandle() const { return m_ft; }

private:
    std::map<std::string, std::shared_ptr<Resource>> m_resources;
    static std::string s_resourcesPath;
    FT_Library m_ft;
};
