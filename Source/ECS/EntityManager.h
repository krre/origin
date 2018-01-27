#pragma once
#include "System.h"
#include "Component.h"
#include <vector>
#include <map>

namespace Origin {

class Entity;
class EntityBuilder;

class EntityManager {

public:
    EntityManager();
    ~EntityManager();

    // Update system
    template <typename T> void addUpdateSystem() {
        auto system = std::make_shared<T>(this);
        updateSystems[system->getType()] = system;
    }

    // Draw system
    template <typename T> void addDrawSystem() {
        auto system = std::make_shared<T>(this);
        drawSystems[system->getType()] = system;
    }

    void removeSystem(SystemType type);
    std::shared_ptr<System> getSystem(SystemType type);
    void clearSystems();

    // Entity
    void addEntity(const std::shared_ptr<Entity>& entity);
    void removeEntity(const std::shared_ptr<Entity>& entity);
    std::shared_ptr<Entity> getEntity(EntityId id);
    void clearEntities();
    std::map<EntityId, std::shared_ptr<Entity>> getEntities() { return entities; }

    // Component
    Component* createComponent(Entity* entity, ComponentType type);
    std::shared_ptr<Entity> createComponents(const std::vector<ComponentType>& types);
    void addComponent(Entity* entity, std::shared_ptr<Component> component);
    void removeComponent(Entity* entity, ComponentType type);

    void update(float dt);
    void draw();

    EntityBuilder* getBuilder() { return entityBuilder.get(); }

private:
    std::map<SystemType, std::shared_ptr<System>> updateSystems;
    std::map<SystemType, std::shared_ptr<System>> drawSystems;
    std::map<EntityId, std::shared_ptr<Entity>> entities;
    std::unique_ptr<EntityBuilder> entityBuilder;

    void initSystems();
};

} // Origin
