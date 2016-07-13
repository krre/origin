#include "../Core/Singleton.h"
#include "System.h"
#include "Entity.h"
#include <vector>

class Engine : public Singleton<Engine> {

public:
    Engine();

    template <typename T> void addSystem() {
        T* system = new T;
        systems[system->getType()] = system;
    }

    void removeSystem(SystemType type);
    System* getSystem(SystemType type);
    void clearSystems();

    void addEntity(Entity* entity);
    void removeEntity(Entity* entity);
    Entity* getEntity(EntityId id);
    void clearEntities();

    std::vector<Entity*> getEntities() { return entities; }

    void process(float dt);

private:
    std::map<SystemType, System*> systems;
    std::vector<Entity*> entities;

    void initSystems();
};
