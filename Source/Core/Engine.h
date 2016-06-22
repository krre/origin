#include "Object.h"
#include "System.h"
#include <list>

class Engine : public Object {

public:
    Engine();

private:
    list<System*> systems;
};
