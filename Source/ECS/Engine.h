#include "../Core/Singleton.h"
#include "System.h"
#include "Entity.h"
#include <vector>

class Engine : public Singleton<Engine> {

public:
    Engine();

    template <typename T> void addSystem() {
        auto system = std::make_shared<T>();
        systems[system->getType()] = system;
    }

    void removeSystem(System::Type type);
    std::shared_ptr<System> getSystem(System::Type type);
    void clearSystems();

    void addEntity(std::shared_ptr<Entity> entity);
    void removeEntity(std::shared_ptr<Entity> entity);
    std::shared_ptr<Entity> getEntity(EntityId id);
    void clearEntities();

    std::vector<std::shared_ptr<Entity>> getEntities() { return entities; }

    void process(float dt);

    Component* createComponent(Entity* entity, Component::Type type);
    void createComponents(Entity* entity, std::vector<Component::Type> types);

private:
    std::map<System::Type, std::shared_ptr<System>> systems;
    std::vector<std::shared_ptr<Entity>> entities;

    void initSystems();
};
