#pragma once
#include "../Component.h"
#include "../Entity.h"
#include <vector>

class NodeComponent : public Component {

public:
    NodeComponent();
    EntityId parent = 0;
    std::vector<EntityId> children;
};
