#pragma once
#include "../Core/Singleton.h"
#include "../Resource/Resource.h"
#include "../UI/Font.h"
#include "../Graphics/OpenGL/Shader.h"
#include <map>

class ResourceManager : public Singleton<ResourceManager> {

public:
    ResourceManager();
    void loadAll();
    void releaseAll();

    Font* getFont(string name);

private:
    map<string, Resource*> resources;
};
