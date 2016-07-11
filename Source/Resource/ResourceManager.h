#pragma once
#include "../Core/Singleton.h"
#include "../Resource/Resource.h"
#include <map>

class ResourceManager : public Singleton<ResourceManager> {

public:
    ResourceManager();
    void loadAll();
    void releaseAll();

private:
    map<string, Resource*> resources;
};
