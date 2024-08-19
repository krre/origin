#pragma once
#include <core/SingleObject.h>

class World : public Core::SingleObject<World> {
public:
    World(Object* parent = nullptr);

    static void create(const std::string& name);
    static void remove(const std::string& name);
    static void load(const std::string& name);
    static void save();

    static std::string savesDirectory();

private:
    std::string m_savePath;
};
