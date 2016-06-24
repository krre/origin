#pragma once
#include "../Component.h"
#include "../Entity.h"
#include <list>

class NodeComponent : public Component {

public:
    NodeComponent();
    EntityId parent;
    list<EntityId> children;
};
