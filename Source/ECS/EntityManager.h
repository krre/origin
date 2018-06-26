#pragma once
#include "Core/SingleObject.h"
#include "System.h"
#include "Component.h"
#include <vector>
#include <map>

namespace Origin {

class Entity;
class EntityBuilder;
class Scene;

class EntityManager : public SingleObject<EntityManager> {

public:
    EntityManager(Object* parent = nullptr);
    ~EntityManager();

    template <typename T> void addSystem() {
        auto system = std::make_shared<T>(this);
        systems[system->getType()] = system;
    }

    void removeSystem(System::Type type);
    std::shared_ptr<System> getSystem(System::Type type);
    void clearSystems();

    // Entity
    void addEntity(const std::shared_ptr<Entity>& entity);
    void removeEntity(const std::shared_ptr<Entity>& entity);
    std::shared_ptr<Entity> getEntity(EntityId id);
    void clearEntities();
    std::map<EntityId, std::shared_ptr<Entity>> getEntities() { return entities; }

    // Component
    Component* createComponent(Entity* entity, Component::Type type);
    std::shared_ptr<Entity> createComponents(const std::vector<Component::Type>& types);
    void addComponent(Entity* entity, std::shared_ptr<Component> component);
    void removeComponent(Entity* entity, Component::Type type);

    void update(Scene* scene, float dt);
    void draw(Scene* scene);

    EntityBuilder* getBuilder() { return entityBuilder.get(); }

private:
    std::map<System::Type, std::shared_ptr<System>> systems;
    std::map<EntityId, std::shared_ptr<Entity>> entities;
    std::unique_ptr<EntityBuilder> entityBuilder;

    void initSystems();
};

} // Origin
