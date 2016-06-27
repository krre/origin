#include "../Core/Singleton.h"
#include "System.h"
#include "Entity.h"
#include <list>

class Engine : public Singleton<Engine> {

public:
    Engine();
    void addSystem(SystemType type);
    void removeSystem(SystemType type);
    const System* getSystem(SystemType type);
    void clearSystems();

    void addEntity(Entity* entity);
    void removeEntity(Entity* entity);
    Entity* getEntity(EntityId id);
    void clearEntities();

    void process(float dt);

private:
    map<SystemType, System*> systems;
    list<Entity*> entities;
};
