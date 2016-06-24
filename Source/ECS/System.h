#pragma once
#include "../Core/Object.h"

class System : public Object {

public:
    System();
    virtual void update(float dt) = 0;
};
