#pragma once
#include "../Core/Singleton.h"
#include "System.h"
#include "Entity.h"
#include <vector>

class Engine : public Singleton<Engine> {

public:
    Engine();

    // System
    template <typename T> void addSystem() {
        auto system = std::make_shared<T>();
        systems[system->getType()] = system;
    }

    void removeSystem(SystemType type);
    std::shared_ptr<System> getSystem(SystemType type);
    void clearSystems();

    // Entity
    void addEntity(std::shared_ptr<Entity> entity);
    void removeEntity(std::shared_ptr<Entity> entity);
    std::shared_ptr<Entity> getEntity(EntityId id);
    void clearEntities();
    std::vector<std::shared_ptr<Entity>> getEntities() { return entities; }

    // Component
    Component* createComponent(Entity* entity, ComponentType type);
    void createComponents(Entity* entity, std::vector<ComponentType> types);
    void addComponent(Entity* entity, std::shared_ptr<Component> component);
    void removeComponent(Entity* entity, ComponentType type);

    void process(float dt);

private:
    std::map<SystemType, std::shared_ptr<System>> systems;
    std::vector<std::shared_ptr<Entity>> entities;

    void initSystems();
};
