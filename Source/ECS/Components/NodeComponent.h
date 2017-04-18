#pragma once
#include "ECS/Entity.h"
#include "ECS/Component.h"
#include <vector>

class NodeComponent : public Component {

public:
    NodeComponent() { type = ComponentType::Node; }
    EntityId parent = 0;
    std::vector<EntityId> children;
};
