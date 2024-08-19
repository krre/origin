#pragma once
#include <core/Object.h>
#include <glm/glm.hpp>

class Entity;

class Scene : public Core::Object {
public:
    Scene(Object* parent = nullptr);

    void setRootEntity(Entity* rootEntity);
    Entity* rootEntity() const { return m_rootEntity; }

private:
    Entity* m_rootEntity = nullptr;
};
