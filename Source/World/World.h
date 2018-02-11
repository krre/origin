#pragma once
#include "Core/Object.h"

namespace Origin {

class World : public Object {

public:
    World(Object* parent = nullptr);

    void create(const std::string& name);
    void load(const std::string& name);
    void save();

    std::string getSavesDirectory();

private:
    std::string savePath;
};

} // Origin
