#include "../Core/Object.h"
#include "System.h"
#include <list>

class Engine : public Object {

public:
    Engine();
    void addSystem(const System* system);
    void removeSystem(const System* system);
    void clearSystems();
    void update(float dt);

private:
    list<const System*> systems;
};
