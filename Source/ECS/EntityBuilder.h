#pragma once
#include "Entity.h"

class EntityBuilder {

public:
    EntityBuilder() {}
    static Entity* ground();
    static Entity* avatar();
    static Entity* camera();
};
