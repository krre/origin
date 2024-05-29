#pragma once
#include "System.h"
#include "Component.h"
#include <core/SingleObject.h>
#include <vector>
#include <map>

class Entity;
class EntityBuilder;
class Scene;

class EntityManager : public Core::SingleObject<EntityManager> {

public:
    EntityManager(Object* parent = nullptr);
    ~EntityManager();

    template <typename T>
    void addSystem() {
        auto system = std::make_shared<T>(this);
        systems[system->getType()] = system;
    }

    void removeSystem(System::Type type);
    std::shared_ptr<System> getSystem(System::Type type);
    void clearSystems();

    // Entity
    void addEntity(const std::shared_ptr<Entity>& entity);
    void removeEntity(const std::shared_ptr<Entity>& entity);
    std::shared_ptr<Entity> getEntity(Core::EntityId id);
    void clearEntities();
    std::map<Core::EntityId, std::shared_ptr<Entity>> getEntities() { return entities; }

    // Component
    Component* createComponent(Entity* entity, Component::Type type);
    std::shared_ptr<Entity> createComponents(const std::vector<Component::Type>& types);
    void addComponent(Entity* entity, std::shared_ptr<Component> component);
    void removeComponent(Entity* entity, Component::Type type);

    void update(Scene* scene, float dt);

    EntityBuilder* getBuilder() { return entityBuilder.get(); }

private:
    std::map<System::Type, std::shared_ptr<System>> systems;
    std::map<Core::EntityId, std::shared_ptr<Entity>> entities;
    std::unique_ptr<EntityBuilder> entityBuilder;

    void initSystems();
};
