#include "../Core/Object.h"
#include "System.h"
#include <list>

class Engine : public Object {

public:
    Engine();
    void addSystem(System* system);
    void removeSystem(System* system);
    void clearSystems();
    void update(float dt);

private:
    list<System*> systems;
};
