#pragma once
#include "../Core/Singleton.h"
#include "../Resource/Resource.h"
#include "../UI/Font.h"
#include "../Graphics/ShaderGroup.h"
#include <map>

class ResourceManager : public Singleton<ResourceManager> {

public:
    ResourceManager();
    void loadAll();

    Font* getFont(const std::string& name);
    ShaderGroup* getShaderGroup(const std::string& name);

private:
    std::map<std::string, std::shared_ptr<Resource>> resources;
    std::string dataPath;
    std::string shaderPath;
    std::string fontPath;
};
