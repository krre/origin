#pragma once
#include "../Entity.h"
#include "../Component.h"
#include <vector>

class NodeComponent : public Component {

public:
    NodeComponent();
    EntityId parent = 0;
    std::vector<EntityId> children;
};
