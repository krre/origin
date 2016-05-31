#pragma once
#include "../Core/Object.h"

class View : public Object {

public:
    View();
    void update(double dt);
    void render();
};
