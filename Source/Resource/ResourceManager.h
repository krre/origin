#pragma once
#include "../Core/Singleton.h"
#include "../Resource/Resource.h"
#include "../UI/Font.h"
#include "../Graphics/Effect.h"
#include <map>

class ResourceManager : public Singleton<ResourceManager> {

public:
    ResourceManager();
    void loadAll();
    void releaseAll();

    Font* getFont(const std::string& name);
    Effect* getEffect(const std::string& name);

private:
    std::map<std::string, Resource*> resources;
};
