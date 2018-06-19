#pragma once
#include "Core/Object.h"

namespace Origin {

class World : public Object {

public:
    World(Object* parent = nullptr);

    static void create(const std::string& name);
    static void remove(const std::string& name);
    static void load(const std::string& name);
    static void save();

    static std::string getSavesDirectory();

private:
    std::string savePath;
};

} // Origin
