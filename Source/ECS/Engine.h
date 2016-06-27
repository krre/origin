#include "../Core/Singleton.h"
#include "System.h"
#include "Entity.h"
#include <list>

class Engine : public Singleton<Engine> {

public:
    Engine();
    void addSystem(System* system);
    void removeSystem(System* system);
    void clearSystems();

    void addEntity(Entity* entity);
    void removeEntity(Entity* entity);
    Entity* getEntity(EntityId id);
    void clearEntities();

    void update(float dt);

private:
    list<System*> systems;
    list<Entity*> entities;
};
