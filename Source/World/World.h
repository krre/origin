#pragma once
#include "Core/Object.h"

namespace Origin {

class World : public Object {

public:
    World(Object* parent = nullptr);
    void create(std::string& filePath);
    void load(std::string& filePath);
    void save();

private:
    std::string filePath;
};

} // Origin
