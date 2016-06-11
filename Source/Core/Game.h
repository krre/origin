#pragma once
#include "Object.h"
#include <list>

class Game : public Object {

public:
    Game();
    void create();
private:
    void cameraMove(float dt);
    void update(float dt);
};
